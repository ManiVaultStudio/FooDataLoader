#pragma once

#include <LoaderPlugin.h>
#include "FooData/FooData.h"

using namespace mv::plugin;

// =============================================================================
// Loader
// =============================================================================

class FooDataLoader : public LoaderPlugin
{
    Q_OBJECT
public:
    FooDataLoader(const PluginFactory* factory);
    ~FooDataLoader(void) override;
    
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

class FooDataLoaderFactory : public LoaderPluginFactory
{
    Q_INTERFACES(mv::plugin::LoaderPluginFactory mv::plugin::PluginFactory)
    Q_OBJECT
    Q_PLUGIN_METADATA(IID   "studio.manivault.FooDataLoader"
                      FILE  "PluginInfo.json")
    
public:
    FooDataLoaderFactory();

    FooDataLoader* produce() override;

    mv::DataTypes supportedDataTypes() const override;
};
