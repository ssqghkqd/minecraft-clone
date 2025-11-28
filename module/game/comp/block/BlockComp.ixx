module;

export module game.comp:block;

export namespace mc
{
enum class BlockType
{
    grass_block,
    cobblestone
};
struct BlockComp
{
    BlockType blockType;

};
}