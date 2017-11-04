#ifndef SIMULATEDDISK_H
#define SIMULATEDDISK_H


class SimulatedDisk
{
	public:
		SimulatedDisk(float mass, float radius, float x, float y); 
		void updatePosition();
		void setVelocity(float x_vel, float y_vel);
		void setPosition(float x, float y);
		float getPositionX();
		float getPositionY();
		float getVelX();
		float getVelY();
		
	private:
		float mass_;
		float radius_;

		float centerPositionX;
		float centerPositionY;
		float linear_velocity_y;
		float linear_velocity_x;
};


#endif