#ifndef K_MST_H
#define K_MST_H

#include "edge.h"

class K_mst
{
private:
  std::vector<Edge> tree;
  double weight;
public:
  K_mst() : weight(0) {}
  K_mst(const std::vector<Edge> &_tree);
  void add_edge(const Edge &e);
	void set_weight(const double w)
	{
			weight = w;
	}
	bool operator < (const K_mst &k) const;
	bool operator > (const K_mst &k) const;
	bool operator == (const K_mst &k) const;
	bool operator != (const K_mst &k) const;
	bool operator <= (const K_mst &k) const;

	bool if_edge_in_tree(const Edge &e) const; //if the edge is in the tree
	void pop(const Edge &e);  //pop an edge
	void add(const Edge &e);  //add an edge
  friend class MST;
};


#endif
