#pragma once

#include <utility>
#include <vector>
#include "types.h"

namespace GLnexus {
namespace diploid {

unsigned genotypes(unsigned n_allele);

std::pair<unsigned,unsigned> gt_alleles(unsigned gt);
unsigned alleles_gt(unsigned a1, unsigned a2);

// Extract genotype log-likelihoods, or Status::NOT_FOUND
Status bcf_get_genotype_log_likelihoods(const bcf_hdr_t* header, bcf1_t *record, std::vector<double>& gll);

// Find zygosity_by_GQ for each allele based on the GT and GQ of the record in
// specified samples. (see types.h for the definition of zygosity_by_GQ)
Status bcf_zygosity_by_GQ(const bcf_hdr_t* header, bcf1_t* record, const std::vector<unsigned>& samples,
                          std::vector<zygosity_by_GQ>& ans);

// This function finds the maximum AQs for each allele in the record, across the given
// subset of sample indices. (see types.h for the definition of AQ)
Status bcf_alleles_topAQ(const bcf_hdr_t* hdr, bcf1_t* record, const std::vector<unsigned>& samples,
                         std::vector<top_AQ>& ans);

// exposed for testing: find alleles' maxAQ for given multi-sample genotype likelihood
// vector
Status alleles_topAQ(unsigned n_allele, unsigned n_sample, const std::vector<unsigned>& samples,
                     const std::vector<double>& gl, std::vector<top_AQ>& ans);

namespace trio {
int mendelian_inconsistencies(int gt_p1, int gt_p2, int gt_ch);
}

}}


