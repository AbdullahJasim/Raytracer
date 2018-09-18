#pragma once
#ifndef SURFACES_LIST
#define SURFACES_LIST

class Surfaces_List : public Render_Surface {
public:
	Render_Surface **list;
	int list_size;

	Surfaces_List() {}
	Surfaces_List(Render_Surface **l, int n) { list = l, list_size = n; }
	virtual bool hit(const Ray& ray, float t_min, float t_max, hit_point& hp) const;
};

bool Surfaces_List::hit(const Ray& ray, float t_min, float t_max, hit_point& hp) const {
	hit_point temp;
	bool hit_anything = false;
	double current_closest = t_max;

	for (int i = 0; i < list_size; i++) {
		if (list[i]->hit(ray, t_min, current_closest, temp)) {
			hit_anything = true;
			current_closest = temp.t;
			hp = temp;
		}
	}

	return hit_anything;
}

#endif