// Author: Enrico Guiraud CERN 11/2021

/*************************************************************************
 * Copyright (C) 1995-2021, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_RDF_RVARIATIONREADER
#define ROOT_RDF_RVARIATIONREADER

#include "RColumnReaderBase.hxx"
#include "RVariationBase.hxx"
#include <Rtypes.h> // Long64_t, R__CLING_PTRCHECK

#include <limits>
#include <type_traits>

namespace ROOT {
namespace Internal {
namespace RDF {

/// Column reader that reads the value for a specific column, variation and slot.
class R__CLING_PTRCHECK(off) RVariationReader final : public ROOT::Detail::RDF::RColumnReaderBase {
   RVariationBase *fVariation;

   /// Non-owning ptr to the value of the variation.
   void *fValuePtr = nullptr;

   /// The slot this value belongs to.
   unsigned int fSlot = std::numeric_limits<unsigned int>::max();

   void *GetImpl(Long64_t entry) final
   {
      fVariation->Update(fSlot, entry);
      return fValuePtr;
   }

public:
   RVariationReader(unsigned int slot, const std::string &colName, const std::string &variationName,
                    RVariationBase &variation)
      : fVariation(&variation), fValuePtr(variation.GetValuePtr(slot, colName, variationName)), fSlot(slot)
   {
   }
};

class RVariationsWithReaders {
   // this is a shared_ptr only because we have to track its lifetime with a weak_ptr that we pass to jitted code
   // (see BookVariationJit). it is never null.
   std::shared_ptr<RVariationBase> fVariation;
   // Column readers for this RVariation for a given variation (map key) and a given slot (vector element).
   std::vector<std::unordered_map<std::string, std::unique_ptr<RVariationReader>>> fReadersPerVariation;

public:
   RVariationsWithReaders(std::shared_ptr<RVariationBase> variation, unsigned int nSlots);
   RVariationBase &GetVariation() const { return *fVariation; }
   RVariationReader &GetReader(unsigned int slot, const std::string &colName, const std::string &variationName);
};

} // namespace RDF
} // namespace Internal
} // namespace ROOT

#endif
