// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package edu.wpi.first.wpilibj.examples.pacgoat.subsystems;

import edu.wpi.first.wpilibj.AnalogGyro;
import edu.wpi.first.wpilibj.CounterBase.EncodingType;
import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.command.Subsystem;
import edu.wpi.first.wpilibj.drive.DifferentialDrive;
import edu.wpi.first.wpilibj.examples.pacgoat.Robot;
import edu.wpi.first.wpilibj.examples.pacgoat.commands.DriveWithJoystick;
import edu.wpi.first.wpilibj.motorcontrol.MotorController;
import edu.wpi.first.wpilibj.motorcontrol.MotorControllerGroup;
import edu.wpi.first.wpilibj.motorcontrol.Victor;

/**
 * The Drivetrain subsystem controls the robot's chassis and reads in information about it's speed
 * and position.
 */
public class Drivetrain extends Subsystem {
  // Subsystem devices
  private final MotorController m_frontLeftCIM = new Victor(1);
  private final MotorController m_frontRightCIM = new Victor(2);
  private final MotorController m_rearLeftCIM = new Victor(3);
  private final MotorController m_rearRightCIM = new Victor(4);
  private final MotorControllerGroup m_leftCIMs =
      new MotorControllerGroup(m_frontLeftCIM, m_rearLeftCIM);
  private final MotorControllerGroup m_rightCIMs =
      new MotorControllerGroup(m_frontRightCIM, m_rearRightCIM);
  private final DifferentialDrive m_drive;
  private final Encoder m_rightEncoder = new Encoder(1, 2, true, EncodingType.k4X);
  private final Encoder m_leftEncoder = new Encoder(3, 4, false, EncodingType.k4X);
  private final AnalogGyro m_gyro = new AnalogGyro(0);

  /** Create a new drivetrain subsystem. */
  public Drivetrain() {
    // Configure drive motors
    addChild("Front Left CIM", (Victor) m_frontLeftCIM);
    addChild("Front Right CIM", (Victor) m_frontRightCIM);
    addChild("Back Left CIM", (Victor) m_rearLeftCIM);
    addChild("Back Right CIM", (Victor) m_rearRightCIM);

    // Configure the DifferentialDrive to reflect the fact that all motors
    // are wired backwards (right is inverted in DifferentialDrive).
    m_leftCIMs.setInverted(true);
    m_rightCIMs.setInverted(true);
    m_drive = new DifferentialDrive(m_leftCIMs, m_rightCIMs);
    m_drive.setSafetyEnabled(true);
    m_drive.setExpiration(0.1);
    m_drive.setMaxOutput(1.0);

    if (Robot.isReal()) { // Converts to feet
      m_rightEncoder.setDistancePerPulse(0.0785398);
      m_leftEncoder.setDistancePerPulse(0.0785398);
    } else {
      // Circumference = diameter in feet * pi. 360 tick simulated encoders.
      m_rightEncoder.setDistancePerPulse((4.0 /* in */ * Math.PI) / (360.0 * 12.0 /* in/ft */));
      m_leftEncoder.setDistancePerPulse((4.0 /* in */ * Math.PI) / (360.0 * 12.0 /* in/ft */));
    }

    addChild("Right Encoder", m_rightEncoder);
    addChild("Left Encoder", m_leftEncoder);

    // Configure gyro
    if (Robot.isReal()) {
      m_gyro.setSensitivity(0.007); // TODO: Handle more gracefully?
    }
    addChild("Gyro", m_gyro);
  }

  /** When other commands aren't using the drivetrain, allow tank drive with the joystick. */
  @Override
  public void initDefaultCommand() {
    setDefaultCommand(new DriveWithJoystick());
  }

  /**
   * Tank drive using a PS3 joystick.
   *
   * @param joy PS3 style joystick to use as the input for tank drive.
   */
  public void tankDrive(Joystick joy) {
    m_drive.tankDrive(joy.getY(), joy.getRawAxis(4));
  }

  /**
   * Tank drive using individual joystick axes.
   *
   * @param leftAxis Left sides value
   * @param rightAxis Right sides value
   */
  public void tankDrive(double leftAxis, double rightAxis) {
    m_drive.tankDrive(leftAxis, rightAxis);
  }

  /** Stop the drivetrain from moving. */
  public void stop() {
    m_drive.tankDrive(0, 0);
  }

  /** The encoder getting the distance and speed of left side of the drivetrain. */
  public Encoder getLeftEncoder() {
    return m_leftEncoder;
  }

  /** The encoder getting the distance and speed of right side of the drivetrain. */
  public Encoder getRightEncoder() {
    return m_rightEncoder;
  }

  /** The current angle of the drivetrain as measured by the Gyro. */
  public double getAngle() {
    return m_gyro.getAngle();
  }
}
