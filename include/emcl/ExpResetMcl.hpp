// SPDX-FileCopyrightText: 2022 Ryuichi Ueda ryuichiueda@gmail.com
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef EXP_PF_HPP__
#define EXP_PF_HPP__

#include "emcl/Mcl.hpp"

#include "rclcpp/rclcpp.hpp"

namespace emcl
{

class ExpResetMcl : public Mcl
{
public:
  ExpResetMcl(const Pose& p, int num, const Scan& scan,
              const std::shared_ptr<OdomModel>& odom_model,
              const std::shared_ptr<LikelihoodFieldMap>& map,
              double alpha_th, double open_space_th,
              double expansion_radius_position, double expansion_radius_orientation);
  ~ExpResetMcl();

  void sensorUpdate(double lidar_x, double lidar_y, double lidar_t, bool inv);

protected:
  rclcpp::Logger logger_{rclcpp::get_logger("emcl")};

private:
  double alpha_threshold_;
  double open_space_threshold_;
  double expansion_radius_position_;
  double expansion_radius_orientation_;

  void expansionReset();
};

} // namespace emcl

#endif
