#ifndef CG1RAYTRACER_GROUPS_BVH_HEADER
#define CG1RAYTRACER_GROUPS_BVH_HEADER
#include <vector>
#include <rt/groups/group.h>
#include <rt/bbox.h>
#include <rt/groups/Node.h>
#include <queue>

const int maxNumberElementsInLeaf = 2;
const int numberBins = 50;

namespace rt
{
    class PrimitiveComparator
    {
    private:
        int dimensionIndex;

    public:
        PrimitiveComparator(int dimensionIndex);
        bool operator()(const Primitive *l, const Primitive *r) const;
        bool operator()(const Primitive *l, float valueToCompare) const;
    };

    class BVH : public Group
    {
    private:
        Primitives unsortedList;
        BVHNode *root = nullptr;
        bool doSAH = true;
    public:
        BVH(bool doSAH = true);
        int numNodes;
        virtual BBox getBounds() const;
        virtual Intersection intersect(const Ray &ray, float previousBestDistance = FLT_MAX) const;
        Intersection intersectNode(const Ray &ray, float previousBestDistance, BVHNode *node) const;
        int getIndexFromPlaneLocation(unsigned int startindex, unsigned int endIncludingIndex, int dimensionIndex, float planeLocation);
        void buildBVH(BVHNode *parentNode, int startIndex, int endIncludingIndex);
        void setBoundingBoxOfNode(BVHNode *node, unsigned int startIndex, unsigned int endIncludingIndex);
        std::pair<int, int> getSplittingIndexAndDimensionSAH(int startIndex, int endIncludingIndex);
        BBox getBBoxOfPrimitives(int startIndex, int endIncludingIndex);
        virtual void rebuildIndex();
        virtual ~BVH();
        virtual void add(Primitive *p);
        virtual void setMaterial(Material *m);
        virtual void setCoordMapper(CoordMapper *cm);

        // Do not use this structure as your node layout:
        // It is inefficient and has a large memory footprint.
        struct SerializedNode
        {
            bool isLeaf;
            BBox bbox;

            // For leaves only
            std::vector<Primitive *> primitives;

            // For internal nodes only
            size_t leftChildId;
            size_t rightChildId;
        };

        // Implement this function if you want to take part in the BVH speed competition
        struct Output
        {
            virtual void setNodeCount(size_t nodeCount) = 0;
            virtual void setRootId(size_t rootId) = 0;
            virtual void writeNode(size_t nodeId, const SerializedNode &node) = 0;
        };
        void serialize(Output &output);

        // Implementing this is optional and not needed for the BVH speed competition,
        // but it will allow you to run the benchmark utility and test your BVH exporter.
        struct Input
        {
            virtual size_t getNodeCount() = 0;
            virtual size_t getRootId() = 0;
            virtual const SerializedNode &readNode(size_t nodeId) = 0;
        };
        void deserialize(Input &input);
    };

} // namespace rt

#endif
