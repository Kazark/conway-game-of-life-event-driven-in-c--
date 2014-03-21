#ifndef _LIVINGNEIGHBORSOFCELLCOUNTED_HPP_
#define _LIVINGNEIGHBORSOFCELLCOUNTED_HPP_

#include "Position.hpp"
#include "Event.hpp"

namespace ConwayGameOfLife {
	struct LivingNeighborsOfCellCounted : public ::EventArchitecture::Event {
        Position cellLocation;
        bool isCellAlive;
        unsigned numberOfLivingNeighbors;
	};
}
#endif
