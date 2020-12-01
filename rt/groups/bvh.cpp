#include <rt/groups/bvh.h>

namespace rt {

BVH::BVH()
{
    this -> root = Node();
    this -> bestIntersection = Intersection::failure();
}

void BVH::rebuildIndex() {
    BBox box = BBox::empty();
    for (Primitive* primitive : this -> primitives) {
        box.extend(primitive->getBounds());
    }
    root.box = box;
    if (primitives.size() > 2){ 
        root.isLeaf = false;
        builder(root, primitives);
    } else {
        root.isLeaf = true;
        root.primitives = this -> primitives;
    }     
    
}

void BVH::builder(Node& n, std::vector<Primitive*> prims) const{
    if (prims.size() < 3) {
        n.isLeaf = true;
        n.primitives = prims;
        return;
    }
    BBox box = n.box;
    float xLength = fabs(box.max.x - box.min.x);
    float yLength = fabs(box.max.y - box.min.y);
    float zLength = fabs(box.max.z - box.min.z);
    Node left = Node();
    Node right = Node();
    std::vector<Primitive*> leftPrims;
    std::vector<Primitive*> rightPrims;
    BBox boxleft;
    BBox boxright;
    if (xLength >= std::max(yLength, zLength)) {
        boxleft = BBox(box.min, Point(box.max.x - xLength/2, box.max.y, box.max.z));
        boxright = BBox(Point(box.min.x + xLength/2, box.min.y, box.min.z), box.max);
    } else if (yLength >= std::max(xLength, zLength)) {
        boxleft = BBox(box.min, Point(box.max.x, box.max.y - yLength/2, box.max.z));
        boxright = BBox(Point(box.min.x, box.min.y + yLength/2, box.min.z), box.max);
    } else if (zLength >= std::max(xLength, yLength)) {
        boxleft = BBox(box.min, Point(box.max.x, box.max.y, box.max.z - zLength/2));
        boxright = BBox(Point(box.min.x, box.min.y, box.min.z + zLength/2), box.max);
    }
    for (Primitive *prim : prims) {
        if (prim->getBounds().overlaps(boxleft)) {
            leftPrims.push_back(prim);
        }
        if (prim->getBounds().overlaps(boxright)) {
            rightPrims.push_back(prim);
        }
    }
    left.box = boxleft;
    right.box = boxright;
    n.left = &left;
    n.right = &right;
    builder(left, leftPrims);
    builder(right, rightPrims);
}

BBox BVH::getBounds() const {
    return root.box;
}

Intersection BVH::intersect(const Ray& ray, float previousBestDistance) const {
    this -> bestIntersection = Intersection::failure();
    std::pair<float, float> t1t2 = root.box.intersect(ray);
    if (t1t2.second >= t1t2.first) intersectNode(ray, root);
    return bestIntersection;
}

void BVH::intersectNode(const Ray& ray, Node& node) const {
    if (node.isLeaf) {
        intersectLeaf(ray, node);
    } else {
        std::pair<float, float> t1t2left = node.left->box.intersect(ray);
        std::pair<float, float> t1t2right = node.right->box.intersect(ray);
        if (t1t2left.second >= t1t2left.first) intersectNode(ray, *node.left);
        if (t1t2right.second >= t1t2right.first) intersectNode(ray, *node.right);
    }
}

void BVH::intersectLeaf(const Ray& ray, Node& node) const {
    if (node.box.min.x > bestIntersection.hitPoint().x && node.box.min.y > bestIntersection.hitPoint().y 
        && node.box.min.z > bestIntersection.hitPoint().z) {
            return;
    }
     for (Primitive* primitive : node.primitives) {
        Intersection hit = primitive->intersect(ray, this->bestIntersection.distance);
        if (hit) {
            this -> bestIntersection = hit;
        }
    }
}

void BVH::add(Primitive* p) {
    this->primitives.push_back(p);
}

void BVH::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void BVH::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

void BVH::serialize(BVH::Output& output) {
    // To implement this function:
    // - Call output.setNodeCount() with the number of nodes in the BVH
    /* TODO */
    // - Set the root node index using output.setRootId()
    /* TODO */
    // - Write each and every one of the BVH nodes to the output using output.writeNode()
    /* TODO */ NOT_IMPLEMENTED;
}
void BVH::deserialize(BVH::Input& input) {
    // To implement this function:
    // - Allocate and initialize input.getNodeCount() nodes
    /* TODO */
    // - Fill your nodes with input.readNode(index)
    /* TODO */
    // - Use the node at index input.getRootId() as the root node
    /* TODO */ NOT_IMPLEMENTED;
}

}