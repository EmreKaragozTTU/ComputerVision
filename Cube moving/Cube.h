#pragma once

#include <SDL.h>
typedef glm::vec3 Vec3;
typedef glm::mat4 Mat4;

enum TransformSpace {
	Local,
	Global
};

class Cube {
public:
	Cube() {
		p0 = Vec3(-0.5, -0.5, 0.5);
		p1 = Vec3(0.5, -0.5, 0.5);
		p2 = Vec3(0.5, 0.5, 0.5);
		p3 = Vec3(-0.5, 0.5, 0.5);

		p4 = Vec3(-0.5, -0.5, -0.5);
		p5 = Vec3(0.5, -0.5, -0.5);
		p6 = Vec3(0.5, 0.5, -0.5);
		p7 = Vec3(-0.5, 0.5, -0.5);

		transformSpace = Global;
		Translate(Vec3(0, 0, 5));
	}

	void Draw() {

		ApplyTransform(); // Apply previous transformations (Translate + Rotate in our case)

		auto projectFn = [](Vec3 &p) -> void {
			// Write your projection code here

			// Build projection matrix
			glm::mat4 proj = glm::perspective(60.0f, 640.0f / 480.0f, 0.1f, 1000.0f);
			p = (proj * glm::vec4(p, 1)).xyz;
		};

		// Transformations
		Vec3 tp0 = (transform * glm::vec4(p0, 1)).xyz;
		Vec3 tp1 = (transform * glm::vec4(p1, 1)).xyz;
		Vec3 tp2 = (transform * glm::vec4(p2, 1)).xyz;
		Vec3 tp3 = (transform * glm::vec4(p3, 1)).xyz;
		Vec3 tp4 = (transform * glm::vec4(p4, 1)).xyz;
		Vec3 tp5 = (transform * glm::vec4(p5, 1)).xyz;
		Vec3 tp6 = (transform * glm::vec4(p6, 1)).xyz;
		Vec3 tp7 = (transform * glm::vec4(p7, 1)).xyz;

		// Projections
		projectFn(tp0);
		projectFn(tp1);
		projectFn(tp2);
		projectFn(tp3);
		projectFn(tp4);
		projectFn(tp5);
		projectFn(tp6);
		projectFn(tp7);

		// Cube drawings
		glBegin(GL_LINES);
		glColor3f(1.f, 1.f, 1.f);

		// Front
		glVertex3f(tp0.x, tp0.y, tp0.z);
		glVertex3f(tp1.x, tp1.y, tp1.z);

		glVertex3f(tp1.x, tp1.y, tp1.z);
		glVertex3f(tp2.x, tp2.y, tp2.z);

		glVertex3f(tp2.x, tp2.y, tp2.z);
		glVertex3f(tp3.x, tp3.y, tp3.z);

		glVertex3f(tp0.x, tp0.y, tp0.z);
		glVertex3f(tp3.x, tp3.y, tp3.z);

		// Back
		glVertex3f(tp4.x, tp4.y, tp4.z);
		glVertex3f(tp5.x, tp5.y, tp5.z);

		glVertex3f(tp5.x, tp5.y, tp5.z);
		glVertex3f(tp6.x, tp6.y, tp6.z);

		glVertex3f(tp6.x, tp6.y, tp6.z);
		glVertex3f(tp7.x, tp7.y, tp7.z);

		glVertex3f(tp7.x, tp7.y, tp7.z);
		glVertex3f(tp4.x, tp4.y, tp4.z);

		// Sides
		glVertex3f(tp0.x, tp0.y, tp0.z);
		glVertex3f(tp4.x, tp4.y, tp4.z);

		glVertex3f(tp1.x, tp1.y, tp1.z);
		glVertex3f(tp5.x, tp5.y, tp5.z);

		glVertex3f(tp2.x, tp2.y, tp2.z);
		glVertex3f(tp6.x, tp6.y, tp6.z);

		glVertex3f(tp3.x, tp3.y, tp3.z);
		glVertex3f(tp7.x, tp7.y, tp7.z);

		// Arrows
		// Write your axis drawing code

		glEnd();
	}

	void Translate(Vec3 translation) {
		// Write your translation code.

		// Translation matrix:
		// | 1  0  0  tx |
		// | 0  1  0  ty |
		// | 0  0  1  tz |
		// | 0  0  0  1  |

		// Build identity matrix
		glm::mat4 mat = glm::mat4(1.0f);

		// Build translation matrix
		mat[0][3] = translation.x;
		mat[1][3] = translation.y;
		mat[2][3] = translation.z;

		translate = mat;
	}

	void Rotate(float angle, Vec3 axis) {
		// Write your rotation code.

		// Build rotation matrix
		glm::mat4 mat = glm::rotate(glm::mat4(1.0f), angle, axis);

		rotate = mat;
	}

	void SwapTs() {
		if (transformSpace == Global)
			transformSpace = Local; // Cube turns around drawn axis
		else
			transformSpace = Global; // Cube turns around world axis
	}

	void ApplyTransform() {
		if (transformSpace == Global) {
			// Write your global transformation code
			transform = translate * rotate;
		}

		if (transformSpace == Local) {
			// Write yout local transformation code
			transform = rotate * translate;
		}

		// Reset transforms
		translate = Mat4();
		rotate = Mat4();
	}

private:
	Mat4 transform;
	Mat4 translate, rotate;
	TransformSpace transformSpace;

	Vec3 p0;
	Vec3 p1;
	Vec3 p2;
	Vec3 p3;
	Vec3 p4;
	Vec3 p5;
	Vec3 p6;
	Vec3 p7;
};
