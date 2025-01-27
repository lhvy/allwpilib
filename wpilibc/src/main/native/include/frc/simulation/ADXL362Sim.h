// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <hal/SimDevice.h>

namespace frc {

class ADXL362;

namespace sim {

/**
 * Class to control a simulated ADXRS450 gyroscope.
 */
class ADXL362Sim {
 public:
  /**
   * Constructs from a ADXL362 object.
   *
   * @param ADXL362 accel to simulate
   */
  explicit ADXL362Sim(const ADXL362& accel);

  /**
   * Sets the X acceleration.
   */
  void SetX(double accel);

  /**
   * Sets the Y acceleration.
   */
  void SetY(double accel);

  /**
   * Sets the Z acceleration.
   */
  void SetZ(double accel);

 private:
  hal::SimDouble m_simX;
  hal::SimDouble m_simY;
  hal::SimDouble m_simZ;
};

}  // namespace sim
}  // namespace frc
