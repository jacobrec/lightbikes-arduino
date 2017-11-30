class LittleGrid {
private:
public:
    Tile *tiles; // tiles here are stored with 4 tiles per byte. tiles[0] holds the 4 tiles that are in the top left corner in a square formation, this is to save space on the arduinos limited memory

    // height and width must be divisible by 2 due to the encoding, this encoding however uses 25% of the memory it would otherwise use
    LittleGrid(int height, int width);
    ~LittleGrid();

    Tile getTile(int x, int y);

    void makeWall(int x, int y, uint8_t);

    int height;
    int width;
};


class Possession_Driver : public Driver_t {
private:
    int calculatePossession(Grid_t *grid, Turn_t test);
    void swap(int *a, int *b);
    virtual void parallelSort(int *comparer, int *latched, int size);

public:
    Turn_t steer(Grid_t *grid);
};
