#ifndef SIMULATEDDISK_H
#define SIMULATEDDISK_H


class SimulatedDisk
{
	public:
		SimulatedDisk(double radius, double x, double y);
		bool updatePosition();
		void setVelocity(double x_vel, double y_vel);
		void setPosition(double x, double y);
        double getPositionX();
        double getPositionY();
        double getVelX();
        double getVelY();
		
	private:
		float radius_;

        double centerPositionX;
        double centerPositionY;
        double linear_velocity_y;
        double linear_velocity_x;
};


#endif