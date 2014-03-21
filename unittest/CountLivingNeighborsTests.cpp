#include "gtest/gtest.h"

#include "CountLivingNeighbors.hpp"
#include "LivingNeighborsOfCellCounted.hpp"
using namespace ::ConwayGameOfLife;
using namespace ::EventArchitecture;

#include "EnhancedPublisherMock.hpp"

struct CountLivingNeighborsTests: public ::testing::Test
{
    CountLivingNeighborsTests() :
        heapAllocator(),
        publisher(heapAllocator),
        objectUnderTest(publisher)
    {
        heapAllocator.registerSubtype<LivingNeighborsOfCellCounted>();
    };

    HeapAllocatorForSubtypesOf<Event> heapAllocator;
    EnhancedPublisherMock publisher;
    CountLivingNeighbors objectUnderTest;
};

TEST_F(CountLivingNeighborsTests, emits_one_event_for_each_cell_in_the_grid_of_the_completed_generation)
{
    GenerationCompleted event = { true, false, true, true };
    objectUnderTest.handle(event);
    EXPECT_EQ(4, publisher.numberOfEventsOfType<LivingNeighborsOfCellCounted>());
}
