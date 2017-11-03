#ifndef SIMULATEDDISK_H
#define SIMULATEDDISK_H


const float gravity = 9.81;

class SimulatedDisk
{
	public:
		SimulatedDisk(float mass, float radius); 
		void updatePosition();
		void setPosition(float x, float y);
		float getPositionX();
		float getPositionY();

	private:
		float mass_;
		float radius_;

		float centerPositionX;
		float centerPositionY;
		float linear_velocity_y;
		float linear_velocity_x;



};


#endif