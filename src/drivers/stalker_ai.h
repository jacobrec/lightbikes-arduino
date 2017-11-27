class Stalker_Driver : public Driver_t {
private:
    int distanceAfterTurn(Turn_t turn, Grid_t *grid);
    bool isTurnSafe(Turn_t turn, Grid_t *grid);

protected:
    void swap(int *a, int *b);
    virtual void parallelSort(int *comparer, int *latched, int size);

public:
    Turn_t steer(Grid_t *grid);
};
