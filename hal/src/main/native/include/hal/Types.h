// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <stdint.h>

/**
 * @defgroup hal_types Type Definitions
 * @ingroup hal_capi
 * @{
 */

#define HAL_kInvalidHandle 0

typedef int32_t HAL_Handle;

typedef HAL_Handle HAL_PortHandle;

typedef HAL_Handle HAL_AnalogInputHandle;

typedef HAL_Handle HAL_AnalogOutputHandle;

typedef HAL_Handle HAL_AnalogTriggerHandle;

typedef HAL_Handle HAL_CompressorHandle;

typedef HAL_Handle HAL_CounterHandle;

typedef HAL_Handle HAL_DigitalHandle;

typedef HAL_Handle HAL_DigitalPWMHandle;

typedef HAL_Handle HAL_EncoderHandle;

typedef HAL_Handle HAL_FPGAEncoderHandle;

typedef HAL_Handle HAL_GyroHandle;

typedef HAL_Handle HAL_InterruptHandle;

typedef HAL_Handle HAL_NotifierHandle;

typedef HAL_Handle HAL_RelayHandle;

typedef HAL_Handle HAL_SolenoidHandle;

typedef HAL_Handle HAL_SerialPortHandle;

typedef HAL_Handle HAL_CANHandle;

typedef HAL_Handle HAL_SimDeviceHandle;

typedef HAL_Handle HAL_SimValueHandle;

typedef HAL_Handle HAL_DMAHandle;

typedef HAL_Handle HAL_DutyCycleHandle;

typedef HAL_Handle HAL_AddressableLEDHandle;

typedef HAL_CANHandle HAL_PDPHandle;

typedef HAL_Handle HAL_PowerDistributionHandle;

typedef HAL_Handle HAL_CTREPCMHandle;

typedef HAL_Handle HAL_REVPDHHandle;

typedef int32_t HAL_Bool;

#ifdef __cplusplus
#define HAL_ENUM(name) enum name : int32_t
#else
#define HAL_ENUM(name)  \
  typedef int32_t name; \
  enum name
#endif

#ifdef __cplusplus
namespace hal {

/**
 * A move-only C++ wrapper around a HAL handle.
 * Does not ensure destruction.
 */
template <typename CType, int32_t CInvalid = HAL_kInvalidHandle>
class Handle {
 public:
  Handle() = default;
  /*implicit*/ Handle(CType val) : m_handle(val) {}  // NOLINT

  Handle(const Handle&) = delete;
  Handle& operator=(const Handle&) = delete;

  Handle(Handle&& rhs) : m_handle(rhs.m_handle) { rhs.m_handle = CInvalid; }

  Handle& operator=(Handle&& rhs) {
    m_handle = rhs.m_handle;
    rhs.m_handle = CInvalid;
    return *this;
  }

  operator CType() const { return m_handle; }  // NOLINT

 private:
  CType m_handle = CInvalid;
};

}  // namespace hal
#endif
/** @} */
