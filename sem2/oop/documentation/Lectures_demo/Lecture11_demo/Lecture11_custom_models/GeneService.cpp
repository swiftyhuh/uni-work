#include "GeneService.h"

GeneService::GeneService(GeneRepository& repo): repo{repo}
{
}

int GeneService::getSize() const
{
	return this->repo.getSize();
}

std::vector<Gene> GeneService::getGenes() const
{
	return this->repo.getGenes();
}

void GeneService::addGene(const std::string& name, const std::string& organismName, const std::string& geneFunction)
{
	Gene g{ name, organismName, geneFunction };
	this->repo.addGene(g);
}

void GeneService::updateGene(int index, const std::string& name, const std::string& organismName, const std::string& geneFunction)
{
	Gene g{ name, organismName, geneFunction };
	this->repo.updateGene(index, g);
}
