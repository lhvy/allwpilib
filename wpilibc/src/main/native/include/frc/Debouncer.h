// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <units/time.h>

#include "frc/Timer.h"

namespace frc {
/**
 * A simple debounce filter for boolean streams.  Requires that the boolean
 * change value from baseline for a specified period of time before the filtered
 * value changes.
 */
class Debouncer {
 public:
  enum DebounceType { kRising, kFalling, kBoth };

  /**
   * Creates a new Debouncer.
   *
   * @param debounce The number of seconds the value must change from
   *                 baseline for the filtered value to change.
   * @param type     Which type of state change the debouncing will be performed
   *                 on.
   */
  explicit Debouncer(units::second_t debounceTime,
                     DebounceType type = DebounceType::kRising);

  /**
   * Applies the debouncer to the input stream.
   *
   * @param input The current value of the input stream.
   * @return The debounced value of the input stream.
   */
  bool Calculate(bool input);

 private:
  frc::Timer m_timer;
  units::second_t m_debounceTime;
  bool m_baseline;
  DebounceType m_debounceType;
};
}  // namespace frc
