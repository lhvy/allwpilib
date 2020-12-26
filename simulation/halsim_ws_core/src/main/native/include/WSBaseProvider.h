// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <functional>
#include <memory>
#include <string>

#include <wpi/json.h>

#include "HALSimBaseWebSocketConnection.h"

namespace wpilibws {

class HALSimWSBaseProvider {
 public:
  explicit HALSimWSBaseProvider(const std::string& key,
                                const std::string& type = "");
  virtual ~HALSimWSBaseProvider() {}

  HALSimWSBaseProvider(const HALSimWSBaseProvider&) = delete;
  HALSimWSBaseProvider& operator=(const HALSimWSBaseProvider&) = delete;

  // Called when the websocket connects. This will cause providers
  // to register their HAL callbacks
  virtual void OnNetworkConnected(
      std::shared_ptr<HALSimBaseWebSocketConnection> ws) = 0;

  // Called when the websocket disconnects. This will cause provider
  // to cancel their HAL callbacks
  virtual void OnNetworkDisconnected() = 0;

  // network -> sim
  virtual void OnNetValueChanged(const wpi::json& json);

  const std::string GetDeviceType() { return m_type; }
  const std::string GetDeviceId() { return m_deviceId; }

 protected:
  // sim -> network
  std::weak_ptr<HALSimBaseWebSocketConnection> m_ws;
  std::string m_key;

  std::string m_type;
  std::string m_deviceId;
};

}  // namespace wpilibws
