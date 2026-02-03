//i have used enum class here because:
//we have a fixed set of simple states: EMPTY, YELLOW, RED
//we need high performance
//States don't have associated behavior - no methods
//we want type safety for those states
enum GridPosition{

    EMPTY, YELLOW, RED
};
// it is just a fixed set of constants
// because it is not enam class GridPosition those constants are global