#pragma once
#include "GeneRepository.h"

class GeneService
{
private:
	GeneRepository& repo;

public:
	GeneService(GeneRepository& repo);

	int getSize() const;
	std::vector<Gene> getGenes() const;

	void addGene(const std::string& name, const std::string& organismName, const std::string& geneFunction);
	void updateGene(int index, const std::string& name, const std::string& organismName, const std::string& geneFunction);
};

