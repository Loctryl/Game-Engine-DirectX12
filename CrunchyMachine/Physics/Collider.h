#pragma once

class Collider {

public:

	Collider();
	Collider(float radius);

	~Collider();
	
	float GetRadius();
private:
	//Tranform* transform;
	float mRadius;

};