// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package edu.wpi.first.wpilibj.can;

import org.junit.jupiter.api.Test;

import edu.wpi.first.hal.HAL;
import edu.wpi.first.hal.can.CANJNI;
import edu.wpi.first.hal.can.CANStatus;

import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;

class CANStatusTest {
  @Test
  void canStatusGetDoesntThrow() {
    HAL.initialize(500, 0);
    CANStatus status = new CANStatus();
    assertDoesNotThrow(() -> CANJNI.GetCANStatus(status));
  }
}
