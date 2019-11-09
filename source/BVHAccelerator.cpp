#include "BVHAccelerator.h"

BVHAccelerator::BVHAccelerator()
{
	root = std::make_shared<Node>();
}

BVHAccelerator::~BVHAccelerator()
{
	
}

bool BVHAccelerator::Hit(Ray const& ray, HitInfo & hitInfo) const
{
	float distance = 0.0f;
	if (root->GetBBox().Hit(ray, distance)) {
		return HitRecursive(ray, hitInfo, root);
	}
	return false;
}

bool BVHAccelerator::HitFast(Ray const & ray) const
{
	float distance = 0.0f;
	if (root->GetBBox().Hit(ray, distance)) {
		return HitRecursiveFast(ray, root);
	}
	return false;
}

void BVHAccelerator::Build(std::vector<Shape*> const & shapes, unsigned int const& maxDepth, unsigned int const& treshold)
{
	// Clear everything from the previous build
	m_shapes.clear();
	root.reset(new Node());
	// If there are no shapes then there is no need to continue
	if (shapes.size() == 0) { return; }
	// Make a copy of the vector of shapes
	m_shapes.reserve(shapes.size());
	copy(shapes.begin(), shapes.end(), back_inserter(m_shapes));
	// Create the world bounding box
	root->CalculateBbox(0, m_shapes.size(), m_shapes);
	BuildRecursive(0, m_shapes.size(), root, 0, maxDepth, treshold);
}

bool BVHAccelerator::HitRecursive(Ray const & ray, HitInfo & hitInfo, std::shared_ptr<const Node> parentNode) const
{
	HitInfo hitInfoTmp;
	if (parentNode->IsLeaf()) {
		for (unsigned int i = parentNode->GetIndex(); i < parentNode->GetIndex() + parentNode->GetNObjs(); i++) {
			if (m_shapes[i]->Hit(ray, hitInfoTmp) && hitInfoTmp.m_distance < hitInfo.m_distance) {
				hitInfo = hitInfoTmp;
			}
		}
		// If the shape stored in the hitInfo does not equal NULL that means we had a hit and we return true
		if (hitInfo.m_shape != NULL) {
			return true;
		}
	}
	else {
		HitInfo hitInfoTmp2;
		float distance = INFINITY;
		float distance2 = INFINITY;
		std::shared_ptr<const Node> leftNode = parentNode->GetLeftNode();
		std::shared_ptr<const Node> rightNode = parentNode->GetRightNode();
		if (leftNode->GetBBox().Hit(ray, distance)) {
			HitRecursive(ray, hitInfoTmp, leftNode);
		}
		if (rightNode->GetBBox().Hit(ray, distance2) && HitRecursive(ray, hitInfoTmp2, rightNode) && hitInfoTmp2.m_distance < hitInfoTmp.m_distance) {
			hitInfo = hitInfoTmp2;
			return true;
		}
		if (hitInfoTmp.m_shape != NULL) {
			hitInfo = hitInfoTmp;
			return true;
		}
	}
	// No nodes or shapes were hit
	return false;
}

bool BVHAccelerator::HitRecursiveFast(Ray const & ray, std::shared_ptr<const Node> parentNode) const
{
	HitInfo hitInfoTmp;
	if (parentNode->IsLeaf()) {
		for (unsigned int i = parentNode->GetIndex(); i < parentNode->GetIndex() + parentNode->GetNObjs(); i++) {
			if (m_shapes[i]->Hit(ray, hitInfoTmp)) {
				return true;
			}
		}
	}
	else {
		float distance = INFINITY;
		std::shared_ptr<const Node> leftNode = parentNode->GetLeftNode();
		std::shared_ptr<const Node> rightNode = parentNode->GetRightNode();
		if (leftNode->GetBBox().Hit(ray, distance) && HitRecursiveFast(ray, leftNode)) {
			return true;
		}
		if (rightNode->GetBBox().Hit(ray, distance) && HitRecursiveFast(ray, rightNode)) {
			return true;
		}
	}
	// No nodes or shapes were hit
	return false;
}

void BVHAccelerator::BuildRecursive(unsigned int const& leftIndex, unsigned int const& rightIndex, std::shared_ptr<Node> parentNode, unsigned int const& depth, unsigned int const& maxDepth, unsigned int const& treshold)
{
	if (rightIndex - leftIndex <= treshold || depth >= maxDepth) {
		parentNode->MakeLeaf(leftIndex, rightIndex - leftIndex);
	}
	else {
		int splitIndex = FindSplitIndexOnGreatestDimension(leftIndex, rightIndex, parentNode);
		if (splitIndex == -1) {
			int diff = rightIndex - leftIndex;
			diff = diff / 2;
			splitIndex = leftIndex + diff;
			if (splitIndex == (int)leftIndex || splitIndex == (int)rightIndex) {
				parentNode->MakeLeaf(leftIndex, rightIndex - leftIndex);
				return;
			}
		}
		parentNode->MakeNodes();
		// Left node
		std::shared_ptr<Node> leftNode = parentNode->GetLeftNode();
		leftNode->CalculateBbox(leftIndex, splitIndex, m_shapes);
		BuildRecursive(leftIndex, splitIndex, leftNode, depth + 1, maxDepth, treshold);
		// Right node
		std::shared_ptr<Node> rightNode = parentNode->GetRightNode();
		rightNode->CalculateBbox(splitIndex, rightIndex, m_shapes);
		BuildRecursive(splitIndex, rightIndex, rightNode, depth + 1, maxDepth, treshold);
	}
}

int BVHAccelerator::FindSplitIndexOnGreatestDimension(unsigned int const& leftIndex, unsigned int const& rightIndex, std::shared_ptr<const Node> parentNode)
{
	ComparePrimitives cmp;
	// Find the highest axis and then try to find the splitIndex
	AABB const& bBox = parentNode->GetBBox();
	vec3 diff =bBox.m_max - bBox.m_min;
	cmp.sort_dim = GetGreatestDimension(diff);
	std::sort(m_shapes.begin() + leftIndex, m_shapes.begin() + rightIndex, cmp);
	unsigned int splitIndex = FindSplitIndex(leftIndex, rightIndex, cmp.sort_dim, parentNode);
	if (splitIndex != leftIndex && splitIndex != rightIndex) {
		return (int)splitIndex;
	}
	// If the split index equals either left or right index then try to split again but in a other dimension
	else {
		diff[cmp.sort_dim] = 0.0f;
		cmp.sort_dim = GetGreatestDimension(diff);
		std::sort(m_shapes.begin() + leftIndex, m_shapes.begin() + rightIndex, cmp);
		splitIndex = FindSplitIndex(leftIndex, rightIndex, cmp.sort_dim, parentNode);
		if (splitIndex != leftIndex && splitIndex != rightIndex) {
			return (int)splitIndex;
		}
		// If the split index still either left or right index then try to split again by the last remaining a dimension
		else {
			diff[cmp.sort_dim] = 0.0f;
			cmp.sort_dim = GetGreatestDimension(diff);
			std::sort(m_shapes.begin() + leftIndex, m_shapes.begin() + rightIndex, cmp);
			splitIndex = FindSplitIndex(leftIndex, rightIndex, cmp.sort_dim, parentNode);
			if (splitIndex != leftIndex && splitIndex != rightIndex) {
				return (int)splitIndex;
			}
			// If there is no split index return -1
			else {
				return -1;
			}
		}
	}
}

int BVHAccelerator::FindSplitIndex(unsigned int const& leftIndex, unsigned int const& rightIndex, unsigned int const& dimension, std::shared_ptr<const Node> parentNode) const
{
	AABB const& bBox = parentNode->GetBBox();
	float split = bBox.m_min[dimension] + (bBox.m_max[dimension] * 0.5f);
	for (unsigned int i = leftIndex; i < rightIndex; i++) {
		if (m_shapes[i]->GetPosition()[dimension] > split) {
			return i;
		}
	}
	return rightIndex;
}

BVHAccelerator::Node::Node()
{
	m_bBox = AABB();
	m_leaf = false;
	m_n_objs = 0;
	m_index = 0;
	m_leftNode = NULL;
	m_rightNode = NULL;
}

BVHAccelerator::Node::~Node()
{

}

void BVHAccelerator::Node::MakeNodes()
{
	m_leftNode = std::make_shared<Node>();
	m_rightNode = std::make_shared<Node>();
}

void BVHAccelerator::Node::MakeLeaf(unsigned int const& index, unsigned int const& n_objs)
{
	m_leaf = true;
	m_index = index;
	m_n_objs = n_objs;
}

void BVHAccelerator::Node::CalculateBbox(unsigned int const & leftIndex, unsigned int const & rightIndex, std::vector<Shape*> const & shapes)
{
	m_bBox = shapes[leftIndex]->GetBbox();
	vec3 pos = shapes[leftIndex]->GetPosition();
	m_bBox.m_min += pos;
	m_bBox.m_max += pos;
	AABB _bBox;
	for (unsigned int i = leftIndex + 1; i < rightIndex; i++) {
		_bBox = shapes[i]->GetBbox();
		pos = shapes[i]->GetPosition();
		_bBox.m_min += pos;
		_bBox.m_max += pos;
		if (_bBox.m_min.m_X < m_bBox.m_min.m_X) { m_bBox.m_min.m_X = _bBox.m_min.m_X; }
		if (_bBox.m_min.m_Y < m_bBox.m_min.m_Y) { m_bBox.m_min.m_Y = _bBox.m_min.m_Y; }
		if (_bBox.m_min.m_Z < m_bBox.m_min.m_Z) { m_bBox.m_min.m_Z = _bBox.m_min.m_Z; }
		if (_bBox.m_max.m_X > m_bBox.m_max.m_X) { m_bBox.m_max.m_X = _bBox.m_max.m_X; }
		if (_bBox.m_max.m_Y > m_bBox.m_max.m_Y) { m_bBox.m_max.m_Y = _bBox.m_max.m_Y; }
		if (_bBox.m_max.m_Z > m_bBox.m_max.m_Z) { m_bBox.m_max.m_Z = _bBox.m_max.m_Z; }
	}
}
