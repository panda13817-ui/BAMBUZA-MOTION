# Bambuza Motion

**Bambuza Components — Stereo Movement Engine**

Original JUCE/C++17 VST3 effect project. Initial source foundation for an advanced, PanMan-inspired rhythmic stereo movement processor.

## Build target
- macOS Intel x86_64 first; Ableton Live 12 validation target.
- VST3 primary; AU and Standalone additionally on macOS.
- JUCE 8.0.10 fetched by CMake.

## GitHub Actions build
Open **Actions → Build Bambuza Motion VST3 (macOS Intel)** and run the workflow manually, or push changes to `main`. The workflow runs DSP tests, compiles the plugin using the macOS Intel runner, checks the binary architecture, and uploads a downloadable artifact named `Bambuza-Motion-macOS-Intel-VST3`.

The artifact is an unsigned development build. It is not notarized or Developer ID signed.

## Local build
Requires Xcode Command Line Tools and CMake 3.22+:

```bash
xcode-select --install
brew install cmake
chmod +x build-macos-intel.command
./build-macos-intel.command
```

## Status — 0.1.0 engineering foundation
Implemented: core pan matrix, envelope follower, modulation shapes, fixed 16-step pattern data, nonlinear saturation prototypes, JUCE processor/editor scaffold, APVTS state persistence.

Not release-ready: host tempo sync, trigger engine integration, full pattern/shape editor, oversampling/alias control, comprehensive stereo/host validation, code signing and notarization. The GitHub build must pass and the plugin must be tested in Ableton Live 12 before calling it usable.
