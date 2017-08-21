#include "ROOT/TBufferMerger.hxx"

#include "TFile.h"
#include "TROOT.h"
#include "TTree.h"

#include <memory>
#include <thread>
#include <iostream>

using namespace std;

#include "ROOT/TThreadedObject.hxx"

namespace ROOT {
template <>  template<class ...ARGS>
TThreadedObject<TTree>::TThreadedObject(ARGS&&... args): fObjPointers(fgMaxSlots, nullptr)
{
   fDirectories = Internal::TThreadedObjectUtils::DirCreator<TTree>::Create(fgMaxSlots);

   TDirectory::TContext ctxt(fDirectories[0]);
   fModel.reset(Internal::TThreadedObjectUtils::Detacher<TTree>::Detach(new TTree(std::forward<ARGS>(args)...)));
   //TFile* f = fModel->GetCurrentFile();
}
} //end namespace ROOT

/*
int WriteTree(size_t nEntries) {
   TFile f("myfile.root"); 
   TTree t("mytree","mytree");
   Fill(&t, 0, nEntries);
   t.Write();
   return 0;
}
*/

void Fill(TTree &tree, int init, int count) {
    int n = 0;
    tree.Branch("n", &n, "n/I");
    for (int i = 0; i < count; ++i) {
       n = init + i;
       tree.Fill();
    }
 } 
 
using namespace ROOT;

int WriteTree(size_t nEntries, size_t nWorkers) {
    size_t nEntriesPerWorker = nEntries/nWorkers;
    EnableThreadSafety();
    TFile file("myfile.root");
    TThreadedObject<TTree> tree("mytree","mytree",99, &file);

    std::vector<std::thread> workers;
    auto workItem = [&](int i) { 
       Fill(tree.GetRef(), i * nEntriesPerWorker, nEntriesPerWorker);
    };

    for (size_t i = 0; i < nWorkers; ++i) workers.emplace_back(workItem,i);
    for (auto&& worker : workers) worker.join();
    tree.Merge();

    return 0;
 }


int _WriteTree(size_t nEntries, size_t nWorkers) {
   size_t nEntriesPerWorker = nEntries/nWorkers;
   ROOT::EnableThreadSafety();
   ROOT::Experimental::TBufferMerger merger("myfile.root");
   std::vector<std::thread> workers;
   auto workItem = [&](int i) {
      auto f = merger.GetFile(); 
      TTree t("random", "random");
      t.ResetBit(kMustCleanup);
      Fill(t, i * nEntriesPerWorker, nEntriesPerWorker);
      f->Write(); // Send content over the wire
   };
   for (size_t i = 0; i < nWorkers; ++i) workers.emplace_back(workItem,i);
   for (auto&& worker : workers) worker.join();
   return 0;
}

int main() {
   WriteTree(1000,10);
   return 0;
}
