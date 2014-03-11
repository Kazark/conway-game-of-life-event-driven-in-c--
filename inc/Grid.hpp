#ifndef _CONWAYGAMEOFLIFE_GRID_HPP_
#define _CONWAYGAMEOFLIFE_GRID_HPP_

#include "ArrayIterator.hpp"

#include <vector>
#include <initializer_list>

namespace ConwayGameOfLife {
    class Cell;
	class Grid {
	public:
        Grid(std::vector<bool>);
        ArrayIterator<const Cell&, Grid> iterator() const;
	private:
        const Cell& operator[](int) const;
        int length() const;

        friend class ArrayIterator<const Cell&, Grid>;

        std::vector<Cell> _gridData;
	};
}
#endif