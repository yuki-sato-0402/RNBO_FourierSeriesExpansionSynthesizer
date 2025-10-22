# RNBO_FourierSeriesExpansionSynthesizer
This is a Synthesiser based on the approximation to triangular, square and sawtooth waves by Fourier series expansion. by RNBO (Max Msp).  

I have also arranged the code to use the [AudioProcessorValueTreeState](https://docs.juce.com/master/classAudioProcessorValueTreeState.html).
Built from the [rnbo.example.juce](https://github.com/Cycling74/rnbo.example.juce).  

For *Getting Started*, please refer to the original repository. Also included in this repository is the C++ program output from RNBO in `export/`. And Max patch is included in `patches/`.

## Demonstration
[Youtube<img width="1421" alt="fourie" src="https://github.com/user-attachments/assets/17d6b8fa-f76d-493b-81e9-6a05eebee25e" />](https://youtu.be/XKcbWMYz5ls)

## Parameter explanation
- **ocillator** : You can choose from three oscillator types: triangle wave, square wave, and sawtooth wave.

- **terms** : You can control the number of sine waves to be combined.

- **amp** : You can control the output gain.

- **filter On Off** : Check this box to apply a low-pass filter.

- **cuttoffOvertone** : This acts like specifying the cutoff frequency, but in this system it is not a frequency, but rather a way to specify which of the synthesized sine waves at which attenuation should begin.

- **attenuation** : You can control the amount of attenuation of the filter.

- **attack, decay, sustain, release** : You can control the ADSR in the same way as with a normal synthesizer.

## System benefits
- Because it is an additive synthesizer, you can manipulate individual sine waves (controlling frequency and amplitude).

- Increasing the number of terms or increasing the frequency can cause aliasing if the top harmonic becomes higher than the Nyquist frequency, so processing is done to prevent this.

## Reference
- [jr-granular](https://github.com/szkkng/jr-granular)  
- [Tutorial:Saving and loading your plug-in state](https://juce.com/tutorials/tutorial_audio_processor_value_tree_state/)
