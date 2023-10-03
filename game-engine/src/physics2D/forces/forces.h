#pragma once

#include "../rigid_body/rigid_body2D.h"

namespace physics2D
{
	namespace forces
	{
		class force_generator
		{
		public:
			virtual void generate_force(rigid_body2D& rigid_body, float delta_time) = 0;
		};

		class force_registry;
		
		class force_registration
		{
		public:
			force_registration(force_generator& force_gen, rigid_body2D& rigid_body);
			force_registration& operator=(const force_registration& other);
			bool operator==(const force_registration& other) const;
		private:
			force_generator& m_force_generator;
			rigid_body2D& m_rigid_body;
		friend class force_registry;
		};

		class force_registry
		{
		public:
			force_registry();
			void add(rigid_body2D& rigid_body, force_generator& force_gen);
			void remove(rigid_body2D& rigid_body, force_generator& force_gen);
			void clear();
			void update_forces(float delta_time);
		private:
			std::vector<force_registration> m_registry;
		};
	}
}