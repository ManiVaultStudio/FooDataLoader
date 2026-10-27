#include "FooDataLoader.h"

#include "noticifaction.h"
#include "FooDataPlugin/FooData.h"

#include "Set.h"

#include <QtCore>
#include <QtDebug>

#include <random>
#include <complex>
#include <vector>

Q_PLUGIN_METADATA(IID "studio.manivault.FooDataLoader")

using namespace mv;

// =============================================================================
// View
// =============================================================================

FooDataLoader::FooDataLoader(const PluginFactory* factory):
    LoaderPlugin(factory),
    _dataSetName("")
{
    
}

FooDataLoader::~FooDataLoader(void)
{
    
}

/**
 * Mandatory plugin override function. Any initial state can be set here.
 * This function gets called when an instance of the plugin is created.
 * In this case when someone select the loader option from the menu.
 */
void FooDataLoader::init()
{
    addNotification(getExampleNotificationMessage());
}

/**
 * Mandatory override function. Gets called when someone selects the Example Loader option
 * from the menu containing loader plugins. This function is responsible for opening the
 * file(s) the user wants to open, process them appropriately and pass the final data to the core.
 */
void FooDataLoader::loadData()
{
    _dataSetName = "FooData";
    auto fooSet = mv::data().createDataset<FooData>("FooData", _dataSetName);
    
    // Create 2D example data by randomly generating 1000 points
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution;

    int numPoints = 1000;
    int numDimensions = 2;

    std::vector<std::complex<float>> exampleData;
    for (int i = 0; i < numPoints * numDimensions; i++)
    {
        exampleData.push_back(std::complex<float>(distribution(generator), distribution(generator)));
    }

    // Passing example data with 1000 points and 2 dimensions
    fooSet->setData(exampleData.data());

    qDebug() << "Number of dimensions: " << exampleData.size() / numPoints;

    // Notify the core system of the new data
    events().notifyDatasetAdded(fooSet);

    qDebug() << "Example file loaded. Num data points: " << fooSet->getNumPoints();
}

FooDataLoaderFactory::FooDataLoaderFactory()
{
    getPluginMetadata().setDescription("Example loader plugin");
    getPluginMetadata().setSummary("This example shows how to implement a data loader plugin in ManiVault Studio.");
    getPluginMetadata().setCopyrightHolder({ "BioVault (Biomedical Visual Analytics Unit LUMC - TU Delft)" });
    getPluginMetadata().setAuthors({
        { "J. Thijssen", { "Software architect" }, { "LUMC", "TU Delft" } },
        { "T. Kroes", { "Lead software architect" }, { "LUMC" } },
        { "A. Vieth",{ "Plugin developer", "Maintainer" },{ "LUMC", "TU Delft" } },
        { "B. van Lew", { "Cat herder", "Maintainer" }, { "LUMC" } }
      });
    getPluginMetadata().setOrganizations({
        { "LUMC", "Leiden University Medical Center", "https://www.lumc.nl/en/" },
        { "TU Delft", "Delft university of technology", "https://www.tudelft.nl/" }
	});
    getPluginMetadata().setLicenseText("This plugin is distributed under the [LGPL v3.0](https://www.gnu.org/licenses/lgpl-3.0.en.html) license.");
}

FooDataLoader* FooDataLoaderFactory::produce()
{
    return new FooDataLoader(this);
}

mv::DataTypes FooDataLoaderFactory::supportedDataTypes() const
{
    DataTypes supportedTypes;
    supportedTypes.append(PointType);
    return supportedTypes;
}
