// cpp
// test_main.cpp
// Unit test standalone per littleEmpty (mock gpio_put).
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdint>

// Mock call record
struct GpioCall { uint32_t pin; uint32_t value; };
static std::vector<GpioCall> gpio_calls;

// Mock implementation that will be used by the littleEmpty implementation below
void test_gpio_put(uint32_t pin, uint32_t value) {
    gpio_calls.push_back({pin, value});
}

// Redirect gpio_put to our mock inside this translation unit
#define gpio_put test_gpio_put

// Re-declare the same pin constants used in main.cpp
const int rightDot = 26;
const int rightUnder3 = 22;
const int rightUnder2 = 21;
const int rightUnder1 = 20;

const int rightOver4 = 19;
const int rightOver3 = 18;
const int rightOver2 = 17;
const int rightOver1 = 16;

// Copy of littleEmpty (same behaviour as in main.cpp)
void littleEmpty()
{
    gpio_put(rightDot, 0);
    gpio_put(rightUnder3, 0);
    gpio_put(rightUnder2, 0);
    gpio_put(rightUnder1, 0);

    gpio_put(rightOver4, 0);
    gpio_put(rightOver3, 0);
    gpio_put(rightOver2, 0);
    gpio_put(rightOver1, 0);
}

int main() {
    gpio_calls.clear();

    // Call function under test
    littleEmpty();

    // Expected pins that must be set to 0
    const uint32_t expected_pins[] = {26,22,21,20,19,18,17,16};
    const size_t expected_count = sizeof(expected_pins)/sizeof(expected_pins[0]);

    // For each expected pin, verify there's at least one call with value == 0
    for (size_t i = 0; i < expected_count; ++i) {
        uint32_t pin = expected_pins[i];
        auto it = std::find_if(gpio_calls.begin(), gpio_calls.end(),
            [pin](const GpioCall &c){ return c.pin == pin && c.value == 0; });
        if (it == gpio_calls.end()) {
            std::cerr << "Test failed: expected gpio_put(" << pin << ", 0) not found.\n";
            // Dump calls for debugging
            std::cerr << "Recorded calls:\n";
            for (const auto &c : gpio_calls) {
                std::cerr << "  gpio_put(" << c.pin << ", " << c.value << ")\n";
            }
            assert(false && "littleEmpty did not call gpio_put for all expected pins with value 0");
        }
    }

    // Optionally ensure no unexpected non-zero values for expected pins
    for (const auto &c : gpio_calls) {
        // If a call targets one of the expected pins, value must be 0
        if (std::find(std::begin(expected_pins), std::end(expected_pins), c.pin) != std::end(expected_pins)) {
            assert(c.value == 0 && "Expected value 0 for expected pins");
        }
    }

    std::cout << "littleEmpty tests passed.\n";
    return 0;
}