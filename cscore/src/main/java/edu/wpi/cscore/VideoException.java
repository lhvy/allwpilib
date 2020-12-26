// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package edu.wpi.cscore;

/**
 * An exception raised by the camera server.
 */
public class VideoException extends RuntimeException {
  private static final long serialVersionUID = -9155939328084105145L;

  public VideoException(String msg) {
    super(msg);
  }

  @Override
  public String toString() {
    return "VideoException [" + super.toString() + "]";
  }
}
