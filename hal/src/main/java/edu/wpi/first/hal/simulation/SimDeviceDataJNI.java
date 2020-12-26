// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package edu.wpi.first.hal.simulation;

import edu.wpi.first.hal.HALValue;
import edu.wpi.first.hal.JNIWrapper;

public class SimDeviceDataJNI extends JNIWrapper {
  public static native void setSimDeviceEnabled(String prefix, boolean enabled);
  public static native boolean isSimDeviceEnabled(String name);

  public static native int registerSimDeviceCreatedCallback(String prefix, SimDeviceCallback callback, boolean initialNotify);
  public static native void cancelSimDeviceCreatedCallback(int uid);

  public static native int registerSimDeviceFreedCallback(String prefix, SimDeviceCallback callback, boolean initialNotify);
  public static native void cancelSimDeviceFreedCallback(int uid);

  public static native int getSimDeviceHandle(String name);

  public static native String getSimDeviceName(int handle);

  public static native int getSimValueDeviceHandle(int handle);

  public static class SimDeviceInfo {
    public SimDeviceInfo(String name, int handle) {
      this.name = name;
      this.handle = handle;
    }

    @SuppressWarnings("MemberName")
    public String name;

    @SuppressWarnings("MemberName")
    public int handle;
  }
  public static native SimDeviceInfo[] enumerateSimDevices(String prefix);

  public static native int registerSimValueCreatedCallback(int device, SimValueCallback callback, boolean initialNotify);
  public static native int registerSimValueCreatedCallback2(int device, SimValueCallback2 callback, boolean initialNotify);
  public static native void cancelSimValueCreatedCallback(int uid);

  public static native int registerSimValueChangedCallback(int handle, SimValueCallback callback, boolean initialNotify);
  public static native int registerSimValueChangedCallback2(int handle, SimValueCallback2 callback, boolean initialNotify);
  public static native void cancelSimValueChangedCallback(int uid);

  public static native int getSimValueHandle(int device, String name);

  public static class SimValueInfo {
    public SimValueInfo(String name, int handle, int direction, int type, long value1, double value2) {
      this.name = name;
      this.handle = handle;
      this.readonly = direction == 1;
      this.direction = direction;
      this.value = HALValue.fromNative(type, value1, value2);
    }

    @SuppressWarnings("MemberName")
    public String name;

    @SuppressWarnings("MemberName")
    public int handle;

    @SuppressWarnings("MemberName")
    @Deprecated
    public boolean readonly;

    @SuppressWarnings("MemberName")
    public int direction;

    @SuppressWarnings("MemberName")
    public HALValue value;
  }
  public static native SimValueInfo[] enumerateSimValues(int device);

  public static native String[] getSimValueEnumOptions(int handle);

  public static native double[] getSimValueEnumDoubleValues(int handle);

  public static native void resetSimDeviceData();
}
