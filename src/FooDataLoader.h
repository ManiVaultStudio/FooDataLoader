#pragma once

#include <LoaderPlugin.h>
#include "FooData/FooDataPlugin.h"

using namespace mv::plugin;

// =============================================================================
// Loader
// =============================================================================

class FooDataLoaderPlugin : public LoaderPlugin
{
    Q_OBJECT
public:
    FooDataLoaderPlugin(const PluginFactory* factory);
    ~FooDataLoaderPlugin(void) override;
    
    void init() override;

    void loadData() Q_DECL_OVERRIDE;

private:
    QString _dataSetName;
    DataFrame _fooDataDf;
    Dataset<Points> _fooData;
    DataFrame _fooMetadata;
};


// =============================================================================
// Factory
// =============================================================================

class FooDataLoaderPluginFactory : public LoaderPluginFactory
{
    Q_INTERFACES(mv::plugin::LoaderPluginFactory mv::plugin::PluginFactory)
    Q_OBJECT
    Q_PLUGIN_METADATA(IID   "studio.manivault.FooDataLoaderPlugin"
                      FILE  "PluginInfo.json")
    
public:
    FooDataLoaderPluginFactory();

    FooDataLoaderPlugin* produce() override;

    mv::DataTypes supportedDataTypes() const override;
};
