#ifndef SIMULATEDDISK_H
#define SIMULATEDDISK_H


class SimulatedDisk
{
	public:
		SimulatedDisk(float radius, float x, float y, float x_vel); 
		bool updatePosition();
		void setVelocity(float x_vel, float y_vel);
		void setPosition(float x, float y);
		float getPositionX();
		float getPositionY();
		float getVelX();
		float getVelY();
		
	private:
		float radius_;

		float centerPositionX;
		float centerPositionY;
		float linear_velocity_y;
		float linear_velocity_x;
};


#endif