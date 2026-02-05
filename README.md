# RNBO_FourierSeriesExpansionSynthesizer
This is a Synthesiser based on the approximation to triangular, square and sawtooth waves by Fourier series expansion. by RNBO (Max Msp).  

This system features the ability to adjust parameters independently for the positive and negative portions of the waveform.   
It also allows the number of terms (the number of sine waves to be combined) to be changed per cycle.

I have also arranged the code to use the [AudioProcessorValueTreeState](https://docs.juce.com/master/classAudioProcessorValueTreeState.html).
Built from the [rnbo.example.juce](https://github.com/Cycling74/rnbo.example.juce).  

For *Getting Started*, please refer to the original repository. Also included in this repository is the C++ program output from RNBO in `export/`. And Max patch is included in `patches/`.

## Demonstration
[Youtube<img width="1144" height="716" alt="Screenshot 2026-02-05 at 22 16 03" src="https://github.com/user-attachments/assets/d86b4108-d3ca-4d50-aa24-77cbcaf8cde5" />](https://youtu.be/pF7NdjODk2U?si=9unfsuFFlacz6mqC)

## Parameter explanation
- **harmonicSeriesMode** :  You can select linear mode or exponential mode for the harmonic series. When the harmonic series is considered as a sequence, the linear mode is an arithmetic progression, and the exponential mode is a geometric progression. Linear mode is more like a timbre, while exponential mode is more like a temperament.

- **harmonicRatio** : You can control the stretching of harmonics. Let $`f_n`$ denote the frequency of the $`n`$ th harmonic and $`f_0`$ the fundamental frequency.    
In the linear mode, the frequency is given by $` f_n = f_0 \times (1 + (n - 1) \times harmonicRatio)`$  
In the exponential mode, the frequency is given by $` f_n = f_0 \times harmonicRatio^{n-1}`$

- **ocillator** : You can choose from three oscillator types: triangle wave, square wave, and sawtooth wave.

- **terms** : You can control the number of sine waves to be combined.

- **amp** : You can control the output gain.

- **filter On Off** : Check this box to apply a low-pass filter.

- **cuttoffOvertone** : This acts like specifying the cutoff frequency, but in this system it is not a frequency, but rather a way to specify which of the synthesized sine waves at which attenuation should begin.

- **attenuation** : You can control the amount of attenuation of the filter.
  
- **Pos Neg** : The parameters will be applied only to the waveform on the selected side (positive side or negative side).

- **PosNegSync** : Synchronize the positive and negative parameters of the waveform. (The adjustment applies to both positive and negative parameters.)

- **cycleCountToAdd** : You can control the number of cycles for which terms are added.

- **cycleCountToSubtract** : You can control the number of cycles for which terms are subtract.

- **termsToAddPerCount** : You can control the terms to be added per cycle. **termsToSubtractPerCount** is automatically calculated as (**termsToAddPerCount** * **cycleCountToAdd** / **cycleCountToSubtract**) , so no configuration is required.

- **attack, decay, sustain, release** : You can control the ADSR in the same way as with a normal synthesizer.


## System benefits
- Because it is an additive synthesizer, you can manipulate individual sine waves (controlling frequency and amplitude).

- Increasing the number of terms or increasing the frequency can cause aliasing if the top harmonic becomes higher than the Nyquist frequency, so processing is done to prevent this.

## Reference
- [jr-granular](https://github.com/szkkng/jr-granular)  
- [Tutorial:Saving and loading your plug-in state](https://juce.com/tutorials/tutorial_audio_processor_value_tree_state/)
