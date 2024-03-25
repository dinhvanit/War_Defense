#ifndef LEVEL_H
#define LEVEL_H


class Level
{

    public:
        Level();
        virtual ~Level();

    protected:

    private:
        enum class TileType : char {
            Tower,
            enemySpawner,
        };
};

#endif // LEVEL_H
