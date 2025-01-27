// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Drivetrain.h"

#include <frc/Joystick.h>
#include <units/length.h>
#include <wpi/numbers>

#include "commands/DriveWithJoystick.h"

Drivetrain::Drivetrain() : frc::Subsystem("Drivetrain") {
  // AddChild("Front Left CIM", m_frontLeftCIM);
  // AddChild("Front Right CIM", m_frontRightCIM);
  // AddChild("Back Left CIM", m_backLeftCIM);
  // AddChild("Back Right CIM", m_backRightCIM);

  // Configure the DifferentialDrive to reflect the fact that all our
  // motors are wired backwards and our drivers sensitivity preferences.
  m_robotDrive.SetSafetyEnabled(false);
  m_robotDrive.SetExpiration(100_ms);
  m_robotDrive.SetMaxOutput(1.0);
  m_leftCIMs.SetInverted(true);
  m_rightCIMs.SetInverted(true);

#ifndef SIMULATION
  // Converts to feet
  m_rightEncoder.SetDistancePerPulse(0.0785398);
  m_leftEncoder.SetDistancePerPulse(0.0785398);
#else
  // Circumference = diameter * pi. 360 tick simulated encoders.
  m_rightEncoder.SetDistancePerPulse(units::foot_t{4_in}.to<double>() *
                                     wpi::numbers::pi / 360.0);
  m_leftEncoder.SetDistancePerPulse(units::foot_t{4_in}.to<double>() *
                                    wpi::numbers::pi / 360.0);
#endif

  AddChild("Right Encoder", m_rightEncoder);
  AddChild("Left Encoder", m_leftEncoder);

// Configure gyro
#ifndef SIMULATION
  m_gyro.SetSensitivity(0.007);  // TODO: Handle more gracefully?
#endif
  AddChild("Gyro", m_gyro);
}

void Drivetrain::InitDefaultCommand() {
  SetDefaultCommand(new DriveWithJoystick());
}

void Drivetrain::TankDrive(double leftAxis, double rightAxis) {
  m_robotDrive.TankDrive(leftAxis, rightAxis);
}

void Drivetrain::Stop() {
  m_robotDrive.TankDrive(0.0, 0.0);
}

frc::Encoder& Drivetrain::GetLeftEncoder() {
  return m_leftEncoder;
}

frc::Encoder& Drivetrain::GetRightEncoder() {
  return m_rightEncoder;
}

double Drivetrain::GetAngle() {
  return m_gyro.GetAngle();
}
