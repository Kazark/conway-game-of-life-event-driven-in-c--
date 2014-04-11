#include "Bus.hpp"
#include "LazyInitContainer.hpp"
#include "Inject.hpp"
#include "DeliverEventsUntilNoneLeft.hpp"
using namespace ::EventArchitecture;

#include "InitiateGameWithRandomGrid.hpp"
#include "CountLivingNeighbors.hpp"
#include "DetermineNextCellState.hpp"
#include "AggregateCellStateChanges.hpp"
using namespace ::ConwayGameOfLife;

int main(int /*argCount*/, char* /*argArray*/[])
{
    LazyInitContainer container;
    container.registerInjector<Router>(Inject<>::Into<Router>);
    container.registerInjector<Channel>(Inject<Router>::Into<Channel>);
    container.registerInjector<Bus>(Inject<Router, Channel>::Into<Bus>);
    container.registerInjector<DeliverEventsUntilNoneLeft>(Inject<Channel>::Into<DeliverEventsUntilNoneLeft>);

    container.registerInjector<InitiateGameWithRandomGrid>(Inject<Bus>::Into<InitiateGameWithRandomGrid>);
    container.registerInjector<CountLivingNeighbors>(Inject<Bus>::Into<CountLivingNeighbors>);
    container.registerInjector<DetermineNextCellState>(Inject<Bus>::Into<DetermineNextCellState>);
    container.registerInjector<AggregateCellStateChanges>(Inject<Bus>::Into<AggregateCellStateChanges>);

    auto bus = container.getInstanceOf<Bus>();
    bus.registerHandler(container.getInstanceOf<CountLivingNeighbors>());
    bus.registerHandler(container.getInstanceOf<DetermineNextCellState>());
    bus.registerHandler<GameInitiated>(container.getInstanceOf<AggregateCellStateChanges>());
    bus.registerHandler<CellStateChanged>(container.getInstanceOf<AggregateCellStateChanges>());

    container.getInstanceOf<InitiateGameWithRandomGrid>().initiate();
    auto mainLoop = container.getInstanceOf<DeliverEventsUntilNoneLeft>();
    mainLoop.run();

    return 0;
}