#pragma once

#include "Shape.h"

#include <vector>

class Node;

class BVHAccelerator
{
public:
	class Node
	{
	public:
		Node();
		~Node();

		unsigned int const& GetNObjs() const { return m_n_objs; }
		unsigned int const& GetIndex() const { return m_index; }
		AABB const& GetBBox() const { return m_bBox; }

		void SetNObjs(unsigned int n_objs) { m_n_objs = n_objs; }
		void SetIndex(unsigned int index) { m_index = index; }

		void MakeNodes();
		std::shared_ptr<Node> GetLeftNode() const { return m_leftNode; }
		std::shared_ptr<Node> const& GetRightNode() const { return m_rightNode; }

		void MakeLeaf(unsigned int const& index, unsigned int const& n_objs);
		bool IsLeaf() const { return m_leaf; }

		void CalculateBbox(unsigned int const& leftIndex, unsigned int const& rightIndex, std::vector<Shape*> const& shapes);

	private:
		unsigned int m_n_objs;
		unsigned int m_index;
		AABB m_bBox;
		std::shared_ptr<Node> m_leftNode;
		std::shared_ptr<Node> m_rightNode;
		bool m_leaf;
	};

	BVHAccelerator();
	~BVHAccelerator();

	bool Hit(Ray const& ray, HitInfo& hitInfo) const;
	// Checks if the ray hits any objects without caring about information about that hit. Usefull for shadow rays
	bool HitFast(Ray const& ray) const;
	void Build(std::vector<Shape*> const& shapes, unsigned int const& maxDepth, unsigned int const& treshold);

private:
	bool HitRecursive(Ray const& ray, HitInfo& hitInfo, std::shared_ptr<const Node> parentNode) const;
	bool HitRecursiveFast(Ray const& ray, std::shared_ptr<const Node> parentNode) const;
	void BuildRecursive(unsigned int const& leftIndex, unsigned int const& rightIndex, std::shared_ptr<Node> parentNode, unsigned int const& depth, unsigned int const& maxDepth, unsigned int const& treshold);

	int FindSplitIndexOnGreatestDimension(unsigned int const& leftIndex, unsigned int const& rightIndex, std::shared_ptr<const Node> parentNode);
	int FindSplitIndex(unsigned int const& leftIndex, unsigned int const& rightIndex, unsigned int const& dimension, std::shared_ptr<const Node> parentNode) const;

	std::vector<Shape*> m_shapes;
	std::shared_ptr<Node> root;

	class ComparePrimitives 
	{
		public:
			bool operator() (Shape* a, Shape* b) {
				AABB box;
				box = a->GetBbox();
				float ca = ((box.m_max[sort_dim] + box.m_min[sort_dim]) * 0.5f) + a->GetPosition()[sort_dim];
				box = b->GetBbox();
				float cb = ((box.m_max[sort_dim] + box.m_min[sort_dim]) * 0.5f) + b->GetPosition()[sort_dim];
				return ca < cb;
			}
			int sort_dim;
	};
};