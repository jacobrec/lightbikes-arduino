class Stalker_Driver : public Driver_t {
private:
    int distanceAfterTurn(Turn_t turn, Grid_t *grid);
    bool isTurnSafe(Turn_t turn, Grid_t *grid);
    void parallelSort(int *comparer, int *latched, int size);
    void swap(int *a, int *b);
public:
    Turn_t steer(Grid_t *grid);
};
