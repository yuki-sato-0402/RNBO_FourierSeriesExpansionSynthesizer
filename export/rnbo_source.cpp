/*******************************************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER $200k in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below $200k annual revenue or funding.

For entities with OVER $200k in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing@cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
*******************************************************************************************************************/

#include "RNBO_Common.h"
#include "RNBO_AudioSignal.h"

namespace RNBO {


#define trunc(x) ((Int)(x))

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

class rnbomatic : public PatcherInterfaceImpl {
public:

rnbomatic()
{
}

~rnbomatic()
{
}

rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
    getEngine()->flushClockEvents(this, -1468824490, false);
    getEngine()->flushClockEvents(this, -62043057, false);
}

template <typename T> void listquicksort(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template <typename T> Int listpartition(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    number x = arr[(Index)h];
    Int i = (Int)(l - 1);

    for (Int j = (Int)(l); j <= h - 1; j++) {
        bool asc = (bool)((bool)(ascending) && arr[(Index)j] <= x);
        bool desc = (bool)((bool)(!(bool)(ascending)) && arr[(Index)j] >= x);

        if ((bool)(asc) || (bool)(desc)) {
            i++;
            this->listswapelements(arr, i, j);
            this->listswapelements(sortindices, i, j);
        }
    }

    i++;
    this->listswapelements(arr, i, h);
    this->listswapelements(sortindices, i, h);
    return i;
}

template <typename T> void listswapelements(T& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

inline number linearinterp(number frac, number x, number y) {
    return x + (y - x) * frac;
}

inline number safemod(number f, number m) {
    if (m != 0) {
        Int f_trunc = (Int)(trunc(f));
        Int m_trunc = (Int)(trunc(m));

        if (f == f_trunc && m == m_trunc) {
            f = f_trunc % m_trunc;
        } else {
            if (m < 0) {
                m = -m;
            }

            if (f >= m) {
                if (f >= m * 2.0) {
                    number d = f / m;
                    Int i = (Int)(trunc(d));
                    d = d - i;
                    f = d * m;
                } else {
                    f -= m;
                }
            } else if (f <= -m) {
                if (f <= -m * 2.0) {
                    number d = f / m;
                    Int i = (Int)(trunc(d));
                    d = d - i;
                    f = d * m;
                } else {
                    f += m;
                }
            }
        }
    } else {
        f = 0.0;
    }

    return f;
}

number wrap(number x, number low, number high) {
    number lo;
    number hi;

    if (low == high)
        return low;

    if (low > high) {
        hi = low;
        lo = high;
    } else {
        lo = low;
        hi = high;
    }

    number range = hi - lo;

    if (x >= lo && x < hi)
        return x;

    if (range <= 0.000000001)
        return lo;

    long numWraps = (long)(trunc((x - lo) / range));
    numWraps = numWraps - ((x < lo ? 1 : 0));
    number result = x - range * numWraps;

    if (result >= hi)
        return result - range;
    else
        return result;
}

template <typename T> inline void poke_default(
    T& buffer,
    SampleValue value,
    SampleValue sampleIndex,
    int channel,
    number overdub
) {
    number bufferSize = buffer->getSize();
    const Index bufferChannels = (const Index)(buffer->getChannels());

    if (bufferSize > 0 && (5 != 5 || (sampleIndex >= 0 && sampleIndex < bufferSize)) && (5 != 5 || (channel >= 0 && channel < bufferChannels))) {
        if (overdub != 0) {
            number currentValue = buffer->getSample(channel, sampleIndex);

            {
                value = value * (1. - overdub) + currentValue * overdub;
            }
        }

        buffer->setSample(channel, sampleIndex, value);
        buffer->setTouched(true);
    }
}

inline number cubicinterp(number a, number w, number x, number y, number z) {
    number a2 = a * a;
    number f0 = z - y - w + x;
    number f1 = w - x - f0;
    number f2 = y - w;
    number f3 = x;
    return f0 * a * a2 + f1 * a2 + f2 * a + f3;
}

inline number splineinterp(number a, number w, number x, number y, number z) {
    number a2 = a * a;
    number f0 = -0.5 * w + 1.5 * x - 1.5 * y + 0.5 * z;
    number f1 = w - 2.5 * x + 2 * y - 0.5 * z;
    number f2 = -0.5 * w + 0.5 * y;
    return f0 * a * a2 + f1 * a2 + f2 * a + x;
}

inline number cosT8(number r) {
    number t84 = 56.0;
    number t83 = 1680.0;
    number t82 = 20160.0;
    number t81 = 2.4801587302e-05;
    number t73 = 42.0;
    number t72 = 840.0;
    number t71 = 1.9841269841e-04;

    if (r < 0.785398163397448309615660845819875721 && r > -0.785398163397448309615660845819875721) {
        number rr = r * r;
        return 1.0 - rr * t81 * (t82 - rr * (t83 - rr * (t84 - rr)));
    } else if (r > 0.0) {
        r -= 1.57079632679489661923132169163975144;
        number rr = r * r;
        return -r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
    } else {
        r += 1.57079632679489661923132169163975144;
        number rr = r * r;
        return r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
    }
}

inline number cosineinterp(number frac, number x, number y) {
    number a2 = (1.0 - this->cosT8(frac * 3.14159265358979323846)) / (number)2.0;
    return x * (1.0 - a2) + y * a2;
}

template <typename T> inline array<SampleValue, 1 + 1> peek_default(T& buffer, SampleValue sampleIndex, Index channelOffset) {
    number bufferSize = buffer->getSize();
    const Index bufferChannels = (const Index)(buffer->getChannels());
    constexpr int ___N2 = 1 + 1;
    array<SampleValue, ___N2> out = FIXEDSIZEARRAYINIT(1 + 1);

    if (bufferSize == 0 || (5 == 5 && (sampleIndex < 0 || sampleIndex >= bufferSize))) {
        return out;
    } else {
        for (Index channel = 0; channel < 1; channel++) {
            Index channelIndex = (Index)(channel + channelOffset);

            {
                if (channelIndex >= bufferChannels || channelIndex < 0) {
                    out[(Index)channel] = 0;
                    continue;
                }
            }

            SampleValue bufferreadsample_result;

            {
                auto& __buffer = buffer;

                if (sampleIndex < 0.0) {
                    bufferreadsample_result = 0.0;
                }

                SampleIndex index1 = (SampleIndex)(trunc(sampleIndex));

                {
                    {
                        {
                            {
                                bufferreadsample_result = __buffer->getSample(channelIndex, index1);
                            }
                        }
                    }
                }
            }

            out[(Index)channel] = bufferreadsample_result;
        }

        out[1] = sampleIndex;
        return out;
    }
}

inline number safediv(number num, number denom) {
    return (denom == 0.0 ? 0.0 : num / denom);
}

number safepow(number base, number exponent) {
    return fixnan(rnbo_pow(base, exponent));
}

number scale(
    number x,
    number lowin,
    number hiin,
    number lowout,
    number highout,
    number pow
) {
    auto inscale = this->safediv(1., hiin - lowin);
    number outdiff = highout - lowout;
    number value = (x - lowin) * inscale;

    if (pow != 1) {
        if (value > 0)
            value = this->safepow(value, pow);
        else
            value = -this->safepow(-value, pow);
    }

    value = value * outdiff + lowout;
    return value;
}

number samplerate() {
    return this->sr;
}

inline number intnum(const number value) {
    return trunc(value);
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

Index vectorsize() {
    return this->vs;
}

SampleIndex currentsampletime() {
    return this->audioProcessSampleCount + this->sampleOffsetIntoNextAudioBuffer;
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

MillisecondTime currenttime() {
    return this->_currentTime;
}

number tempo() {
    return this->getTopLevelPatcher()->globaltransport_getTempo(this->currenttime());
}

number mstobeats(number ms) {
    return ms * this->tempo() * 0.008 / (number)480;
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

Index getNumMidiInputPorts() const {
    return 1;
}

void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
    this->updateTime(time);
    this->notein_01_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
}

Index getNumMidiOutputPorts() const {
    return 0;
}

void process(
    const SampleValue * const* inputs,
    Index numInputs,
    SampleValue * const* outputs,
    Index numOutputs,
    Index n
) {
    RNBO_UNUSED(numInputs);
    RNBO_UNUSED(inputs);
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime());
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);

    this->gen_01_perform(
        this->gen_01_in1,
        this->gen_01_termsToAddPerCount,
        this->gen_01_cycleCountToSubtract,
        this->gen_01_cycleCountToAdd,
        this->gen_01_PosNegSync,
        this->gen_01_PosNeg,
        this->gen_01_ocillator,
        this->gen_01_attenuation,
        this->gen_01_cutoffOvertone,
        this->gen_01_filterOnOff,
        this->gen_01_terms,
        this->signals[0],
        n
    );

    this->adsr_01_perform(
        this->adsr_01_attack,
        this->adsr_01_decay,
        this->adsr_01_sustain,
        this->adsr_01_release,
        this->zeroBuffer,
        this->signals[1],
        n
    );

    this->rampsmooth_tilde_01_perform(
        this->signals[1],
        this->rampsmooth_tilde_01_up,
        this->rampsmooth_tilde_01_down,
        this->signals[2],
        n
    );

    this->dspexpr_02_perform(this->signals[0], this->signals[2], this->signals[1], n);
    this->linetilde_01_perform(this->signals[2], n);
    this->dspexpr_01_perform(this->signals[1], this->signals[2], out1, n);
    this->signalforwarder_01_perform(out1, out2, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 3; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->adsr_01_triggerBuf = resizeSignal(this->adsr_01_triggerBuf, this->maxvs, maxBlockSize);
        this->adsr_01_triggerValueBuf = resizeSignal(this->adsr_01_triggerValueBuf, this->maxvs, maxBlockSize);
        this->globaltransport_tempo = resizeSignal(this->globaltransport_tempo, this->maxvs, maxBlockSize);
        this->globaltransport_state = resizeSignal(this->globaltransport_state, this->maxvs, maxBlockSize);
        this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
        this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
        this->didAllocateSignals = true;
    }

    const bool sampleRateChanged = sampleRate != this->sr;
    const bool maxvsChanged = maxBlockSize != this->maxvs;
    const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;

    if (sampleRateChanged || maxvsChanged) {
        this->vs = maxBlockSize;
        this->maxvs = maxBlockSize;
        this->sr = sampleRate;
        this->invsr = 1 / sampleRate;
    }

    this->gen_01_dspsetup(forceDSPSetup);
    this->adsr_01_dspsetup(forceDSPSetup);
    this->rampsmooth_tilde_01_dspsetup(forceDSPSetup);
    this->globaltransport_dspsetup(forceDSPSetup);

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

void setProbingTarget(MessageTag id) {
    switch (id) {
    default:
        {
        this->setProbingIndex(-1);
        break;
        }
    }
}

void setProbingIndex(ProbingIndex ) {}

Index getProbingChannels(MessageTag outletId) const {
    RNBO_UNUSED(outletId);
    return 0;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    case 0:
        {
        return addressOf(this->manageParam);
        break;
        }
    case 1:
        {
        return addressOf(this->RNBODefaultMtofLookupTable256);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 2;
}

void fillRNBODefaultMtofLookupTable256(DataRef& ref) {
    Float64BufferRef buffer;
    buffer = new Float64Buffer(ref);
    number bufsize = buffer->getSize();

    for (Index i = 0; i < bufsize; i++) {
        number midivalue = -256. + (number)512. / (bufsize - 1) * i;
        buffer[i] = rnbo_exp(.057762265 * (midivalue - 69.0));
    }
}

void fillDataRef(DataRefIndex index, DataRef& ref) {
    switch (index) {
    case 1:
        {
        this->fillRNBODefaultMtofLookupTable256(ref);
        break;
        }
    }
}

void zeroDataRef(DataRef& ref) {
    ref->setZero();
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->updateTime(time);

    if (index == 0) {
        this->gen_01_manageParam = new Float64Buffer(this->manageParam);
    }

    if (index == 1) {
        this->gen_01_mtof_17_buffer = new Float64Buffer(this->RNBODefaultMtofLookupTable256);
        this->gen_01_mtof_19_buffer = new Float64Buffer(this->RNBODefaultMtofLookupTable256);
        this->gen_01_mtof_22_buffer = new Float64Buffer(this->RNBODefaultMtofLookupTable256);
        this->gen_01_mtof_56_buffer = new Float64Buffer(this->RNBODefaultMtofLookupTable256);
        this->gen_01_mtof_75_buffer = new Float64Buffer(this->RNBODefaultMtofLookupTable256);
    }
}

void initialize() {
    this->manageParam = initDataRef("manageParam", true, nullptr, "buffer~");
    this->RNBODefaultMtofLookupTable256 = initDataRef("RNBODefaultMtofLookupTable256", true, nullptr, "buffer~");
    this->assign_defaults();
    this->setState();
    this->manageParam->setIndex(0);
    this->gen_01_manageParam = new Float64Buffer(this->manageParam);
    this->RNBODefaultMtofLookupTable256->setIndex(1);
    this->gen_01_mtof_17_buffer = new Float64Buffer(this->RNBODefaultMtofLookupTable256);
    this->gen_01_mtof_19_buffer = new Float64Buffer(this->RNBODefaultMtofLookupTable256);
    this->gen_01_mtof_22_buffer = new Float64Buffer(this->RNBODefaultMtofLookupTable256);
    this->gen_01_mtof_56_buffer = new Float64Buffer(this->RNBODefaultMtofLookupTable256);
    this->gen_01_mtof_75_buffer = new Float64Buffer(this->RNBODefaultMtofLookupTable256);
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

Index getPatcherSerial() const {
    return 0;
}

void getState(PatcherStateInterface& ) {}

void setState() {}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
    this->param_01_getPresetValue(getSubState(preset, "PosNeg"));
    this->param_02_getPresetValue(getSubState(preset, "decay"));
    this->param_03_getPresetValue(getSubState(preset, "attack"));
    this->param_04_getPresetValue(getSubState(preset, "ocillator"));
    this->param_05_getPresetValue(getSubState(preset, "amp"));
    this->param_06_getPresetValue(getSubState(preset, "attenuation"));
    this->param_07_getPresetValue(getSubState(preset, "cutoffOvertone"));
    this->param_08_getPresetValue(getSubState(preset, "filterOnOff"));
    this->param_09_getPresetValue(getSubState(preset, "terms"));
    this->param_10_getPresetValue(getSubState(preset, "release"));
    this->param_11_getPresetValue(getSubState(preset, "sustain"));
    this->param_12_getPresetValue(getSubState(preset, "PosNegSync"));
    this->param_13_getPresetValue(getSubState(preset, "termsToAddPerCount"));
    this->param_14_getPresetValue(getSubState(preset, "cycleCountToSubtract"));
    this->param_15_getPresetValue(getSubState(preset, "cycleCountToAdd"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_01_setPresetValue(getSubState(preset, "PosNeg"));
    this->param_02_setPresetValue(getSubState(preset, "decay"));
    this->param_03_setPresetValue(getSubState(preset, "attack"));
    this->param_04_setPresetValue(getSubState(preset, "ocillator"));
    this->param_05_setPresetValue(getSubState(preset, "amp"));
    this->param_06_setPresetValue(getSubState(preset, "attenuation"));
    this->param_07_setPresetValue(getSubState(preset, "cutoffOvertone"));
    this->param_08_setPresetValue(getSubState(preset, "filterOnOff"));
    this->param_09_setPresetValue(getSubState(preset, "terms"));
    this->param_10_setPresetValue(getSubState(preset, "release"));
    this->param_11_setPresetValue(getSubState(preset, "sustain"));
    this->param_12_setPresetValue(getSubState(preset, "PosNegSync"));
    this->param_13_setPresetValue(getSubState(preset, "termsToAddPerCount"));
    this->param_14_setPresetValue(getSubState(preset, "cycleCountToSubtract"));
    this->param_15_setPresetValue(getSubState(preset, "cycleCountToAdd"));
}

void processTempoEvent(MillisecondTime time, Tempo tempo) {
    this->updateTime(time);

    if (this->globaltransport_setTempo(this->_currentTime, tempo, false))
        {}
}

void processTransportEvent(MillisecondTime time, TransportState state) {
    this->updateTime(time);

    if (this->globaltransport_setState(this->_currentTime, state, false))
        {}
}

void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
    this->updateTime(time);

    if (this->globaltransport_setBeatTime(this->_currentTime, beattime, false))
        {}
}

void onSampleRateChanged(double ) {}

void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
    this->updateTime(time);

    if (this->globaltransport_setTimeSignature(this->_currentTime, numerator, denominator, false))
        {}
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time);

    switch (index) {
    case 0:
        {
        this->param_01_value_set(v);
        break;
        }
    case 1:
        {
        this->param_02_value_set(v);
        break;
        }
    case 2:
        {
        this->param_03_value_set(v);
        break;
        }
    case 3:
        {
        this->param_04_value_set(v);
        break;
        }
    case 4:
        {
        this->param_05_value_set(v);
        break;
        }
    case 5:
        {
        this->param_06_value_set(v);
        break;
        }
    case 6:
        {
        this->param_07_value_set(v);
        break;
        }
    case 7:
        {
        this->param_08_value_set(v);
        break;
        }
    case 8:
        {
        this->param_09_value_set(v);
        break;
        }
    case 9:
        {
        this->param_10_value_set(v);
        break;
        }
    case 10:
        {
        this->param_11_value_set(v);
        break;
        }
    case 11:
        {
        this->param_12_value_set(v);
        break;
        }
    case 12:
        {
        this->param_13_value_set(v);
        break;
        }
    case 13:
        {
        this->param_14_value_set(v);
        break;
        }
    case 14:
        {
        this->param_15_value_set(v);
        break;
        }
    }
}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
    this->setParameterValue(index, this->getParameterValue(index), time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    case 0:
        {
        return this->param_01_value;
        }
    case 1:
        {
        return this->param_02_value;
        }
    case 2:
        {
        return this->param_03_value;
        }
    case 3:
        {
        return this->param_04_value;
        }
    case 4:
        {
        return this->param_05_value;
        }
    case 5:
        {
        return this->param_06_value;
        }
    case 6:
        {
        return this->param_07_value;
        }
    case 7:
        {
        return this->param_08_value;
        }
    case 8:
        {
        return this->param_09_value;
        }
    case 9:
        {
        return this->param_10_value;
        }
    case 10:
        {
        return this->param_11_value;
        }
    case 11:
        {
        return this->param_12_value;
        }
    case 12:
        {
        return this->param_13_value;
        }
    case 13:
        {
        return this->param_14_value;
        }
    case 14:
        {
        return this->param_15_value;
        }
    default:
        {
        return 0;
        }
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 15;
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "PosNeg";
        }
    case 1:
        {
        return "decay";
        }
    case 2:
        {
        return "attack";
        }
    case 3:
        {
        return "ocillator";
        }
    case 4:
        {
        return "amp";
        }
    case 5:
        {
        return "attenuation";
        }
    case 6:
        {
        return "cutoffOvertone";
        }
    case 7:
        {
        return "filterOnOff";
        }
    case 8:
        {
        return "terms";
        }
    case 9:
        {
        return "release";
        }
    case 10:
        {
        return "sustain";
        }
    case 11:
        {
        return "PosNegSync";
        }
    case 12:
        {
        return "termsToAddPerCount";
        }
    case 13:
        {
        return "cycleCountToSubtract";
        }
    case 14:
        {
        return "cycleCountToAdd";
        }
    default:
        {
        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "PosNeg";
        }
    case 1:
        {
        return "decay";
        }
    case 2:
        {
        return "attack";
        }
    case 3:
        {
        return "ocillator";
        }
    case 4:
        {
        return "amp";
        }
    case 5:
        {
        return "attenuation";
        }
    case 6:
        {
        return "cutoffOvertone";
        }
    case 7:
        {
        return "filterOnOff";
        }
    case 8:
        {
        return "terms";
        }
    case 9:
        {
        return "release";
        }
    case 10:
        {
        return "sustain";
        }
    case 11:
        {
        return "PosNegSync";
        }
    case 12:
        {
        return "termsToAddPerCount";
        }
    case 13:
        {
        return "cycleCountToSubtract";
        }
    case 14:
        {
        return "cycleCountToAdd";
        }
    default:
        {
        return "bogus";
        }
    }
}

void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
    {
        switch (index) {
        case 0:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 1:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 100;
            info->min = 1;
            info->max = 1000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 2:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 10;
            info->min = 1;
            info->max = 1000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 3:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 1;
            info->max = 3;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 4:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.5;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 5:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 1;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 6:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 2;
            info->min = 2;
            info->max = 40;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 7:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 8:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 1;
            info->max = 40;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 9:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1000;
            info->min = 0;
            info->max = 5000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 10:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 80;
            info->min = 0;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 11:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 12:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 1;
            info->max = 20;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 13:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 20;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 14:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 20;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        }
    }
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
    if (steps == 1) {
        if (normalizedValue > 0) {
            normalizedValue = 1.;
        }
    } else {
        ParameterValue oneStep = (number)1. / (steps - 1);
        ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
        normalizedValue = numberOfSteps * oneStep;
    }

    return normalizedValue;
}

ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
    case 4:
    case 7:
    case 11:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);
            return normalizedValue;
        }
        }
    case 13:
    case 14:
        {
        {
            value = (value < 0 ? 0 : (value > 20 ? 20 : value));
            ParameterValue normalizedValue = (value - 0) / (20 - 0);
            return normalizedValue;
        }
        }
    case 10:
        {
        {
            value = (value < 0 ? 0 : (value > 100 ? 100 : value));
            ParameterValue normalizedValue = (value - 0) / (100 - 0);
            return normalizedValue;
        }
        }
    case 9:
        {
        {
            value = (value < 0 ? 0 : (value > 5000 ? 5000 : value));
            ParameterValue normalizedValue = (value - 0) / (5000 - 0);
            return normalizedValue;
        }
        }
    case 3:
        {
        {
            value = (value < 1 ? 1 : (value > 3 ? 3 : value));
            ParameterValue normalizedValue = (value - 1) / (3 - 1);
            return normalizedValue;
        }
        }
    case 12:
        {
        {
            value = (value < 1 ? 1 : (value > 20 ? 20 : value));
            ParameterValue normalizedValue = (value - 1) / (20 - 1);
            return normalizedValue;
        }
        }
    case 8:
        {
        {
            value = (value < 1 ? 1 : (value > 40 ? 40 : value));
            ParameterValue normalizedValue = (value - 1) / (40 - 1);
            return normalizedValue;
        }
        }
    case 5:
        {
        {
            value = (value < 1 ? 1 : (value > 100 ? 100 : value));
            ParameterValue normalizedValue = (value - 1) / (100 - 1);
            return normalizedValue;
        }
        }
    case 1:
    case 2:
        {
        {
            value = (value < 1 ? 1 : (value > 1000 ? 1000 : value));
            ParameterValue normalizedValue = (value - 1) / (1000 - 1);
            return normalizedValue;
        }
        }
    case 6:
        {
        {
            value = (value < 2 ? 2 : (value > 40 ? 40 : value));
            ParameterValue normalizedValue = (value - 2) / (40 - 2);
            return normalizedValue;
        }
        }
    default:
        {
        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 0:
    case 4:
    case 7:
    case 11:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 13:
    case 14:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (20 - 0);
            }
        }
        }
    case 10:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (100 - 0);
            }
        }
        }
    case 9:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (5000 - 0);
            }
        }
        }
    case 3:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 1 + value * (3 - 1);
            }
        }
        }
    case 12:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 1 + value * (20 - 1);
            }
        }
        }
    case 8:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 1 + value * (40 - 1);
            }
        }
        }
    case 5:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 1 + value * (100 - 1);
            }
        }
        }
    case 1:
    case 2:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 1 + value * (1000 - 1);
            }
        }
        }
    case 6:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 2 + value * (40 - 2);
            }
        }
        }
    default:
        {
        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        return this->param_01_value_constrain(value);
        }
    case 1:
        {
        return this->param_02_value_constrain(value);
        }
    case 2:
        {
        return this->param_03_value_constrain(value);
        }
    case 3:
        {
        return this->param_04_value_constrain(value);
        }
    case 4:
        {
        return this->param_05_value_constrain(value);
        }
    case 5:
        {
        return this->param_06_value_constrain(value);
        }
    case 6:
        {
        return this->param_07_value_constrain(value);
        }
    case 7:
        {
        return this->param_08_value_constrain(value);
        }
    case 8:
        {
        return this->param_09_value_constrain(value);
        }
    case 9:
        {
        return this->param_10_value_constrain(value);
        }
    case 10:
        {
        return this->param_11_value_constrain(value);
        }
    case 11:
        {
        return this->param_12_value_constrain(value);
        }
    case 12:
        {
        return this->param_13_value_constrain(value);
        }
    case 13:
        {
        return this->param_14_value_constrain(value);
        }
    case 14:
        {
        return this->param_15_value_constrain(value);
        }
    default:
        {
        return value;
        }
    }
}

void scheduleParamInit(ParameterIndex index, Index order) {
    this->paramInitIndices->push(index);
    this->paramInitOrder->push(order);
}

void processParamInitEvents() {
    this->listquicksort(
        this->paramInitOrder,
        this->paramInitIndices,
        0,
        (int)(this->paramInitOrder->length - 1),
        true
    );

    for (Index i = 0; i < this->paramInitOrder->length; i++) {
        this->getEngine()->scheduleParameterBang(this->paramInitIndices[i], 0);
    }
}

void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
    RNBO_UNUSED(value);
    RNBO_UNUSED(hasValue);
    this->updateTime(time);

    switch (index) {
    case -1468824490:
        {
        this->adsr_01_mute_bang();
        break;
        }
    case -62043057:
        {
        this->linetilde_01_target_bang();
        break;
        }
    }
}

void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}

void processOutletEvent(
    EngineLink* sender,
    OutletIndex index,
    ParameterValue value,
    MillisecondTime time
) {
    this->updateTime(time);
    this->processOutletAtCurrentTime(sender, index, value);
}

void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
    this->updateTime(time);

    switch (tag) {
    case TAG("valin"):
        {
        if (TAG("number_obj-26") == objectId)
            this->numberobj_01_valin_set(payload);

        break;
        }
    case TAG("format"):
        {
        if (TAG("number_obj-26") == objectId)
            this->numberobj_01_format_set(payload);

        break;
        }
    }
}

void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}

void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {
    case TAG("valout"):
        {
        return "valout";
        }
    case TAG("number_obj-26"):
        {
        return "number_obj-26";
        }
    case TAG("setup"):
        {
        return "setup";
        }
    case TAG("valin"):
        {
        return "valin";
        }
    case TAG("format"):
        {
        return "format";
        }
    }

    return "";
}

MessageIndex getNumMessages() const {
    return 0;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {

    }

    return NullMessageInfo;
}

protected:

void param_01_value_set(number v) {
    v = this->param_01_value_constrain(v);
    this->param_01_value = v;
    this->sendParameter(0, false);

    if (this->param_01_value != this->param_01_lastValue) {
        this->getEngine()->presetTouched();
        this->param_01_lastValue = this->param_01_value;
    }

    this->gen_01_PosNeg_set(v);
}

void param_02_value_set(number v) {
    v = this->param_02_value_constrain(v);
    this->param_02_value = v;
    this->sendParameter(1, false);

    if (this->param_02_value != this->param_02_lastValue) {
        this->getEngine()->presetTouched();
        this->param_02_lastValue = this->param_02_value;
    }

    this->adsr_01_decay_set(v);
}

void param_03_value_set(number v) {
    v = this->param_03_value_constrain(v);
    this->param_03_value = v;
    this->sendParameter(2, false);

    if (this->param_03_value != this->param_03_lastValue) {
        this->getEngine()->presetTouched();
        this->param_03_lastValue = this->param_03_value;
    }

    this->adsr_01_attack_set(v);
}

void param_04_value_set(number v) {
    v = this->param_04_value_constrain(v);
    this->param_04_value = v;
    this->sendParameter(3, false);

    if (this->param_04_value != this->param_04_lastValue) {
        this->getEngine()->presetTouched();
        this->param_04_lastValue = this->param_04_value;
    }

    this->gen_01_ocillator_set(v);
}

void param_05_value_set(number v) {
    v = this->param_05_value_constrain(v);
    this->param_05_value = v;
    this->sendParameter(4, false);

    if (this->param_05_value != this->param_05_lastValue) {
        this->getEngine()->presetTouched();
        this->param_05_lastValue = this->param_05_value;
    }

    {
        list converted = {v};
        this->linetilde_01_segments_set(converted);
    }
}

void param_06_value_set(number v) {
    v = this->param_06_value_constrain(v);
    this->param_06_value = v;
    this->sendParameter(5, false);

    if (this->param_06_value != this->param_06_lastValue) {
        this->getEngine()->presetTouched();
        this->param_06_lastValue = this->param_06_value;
    }

    this->expr_04_in1_set(v);
}

void param_07_value_set(number v) {
    v = this->param_07_value_constrain(v);
    this->param_07_value = v;
    this->sendParameter(6, false);

    if (this->param_07_value != this->param_07_lastValue) {
        this->getEngine()->presetTouched();
        this->param_07_lastValue = this->param_07_value;
    }

    this->gen_01_cutoffOvertone_set(v);
}

void param_08_value_set(number v) {
    v = this->param_08_value_constrain(v);
    this->param_08_value = v;
    this->sendParameter(7, false);

    if (this->param_08_value != this->param_08_lastValue) {
        this->getEngine()->presetTouched();
        this->param_08_lastValue = this->param_08_value;
    }

    this->gen_01_filterOnOff_set(v);
}

void param_09_value_set(number v) {
    v = this->param_09_value_constrain(v);
    this->param_09_value = v;
    this->sendParameter(8, false);

    if (this->param_09_value != this->param_09_lastValue) {
        this->getEngine()->presetTouched();
        this->param_09_lastValue = this->param_09_value;
    }

    this->gen_01_terms_set(v);
}

void param_10_value_set(number v) {
    v = this->param_10_value_constrain(v);
    this->param_10_value = v;
    this->sendParameter(9, false);

    if (this->param_10_value != this->param_10_lastValue) {
        this->getEngine()->presetTouched();
        this->param_10_lastValue = this->param_10_value;
    }

    this->adsr_01_release_set(v);
}

void param_11_value_set(number v) {
    v = this->param_11_value_constrain(v);
    this->param_11_value = v;
    this->sendParameter(10, false);

    if (this->param_11_value != this->param_11_lastValue) {
        this->getEngine()->presetTouched();
        this->param_11_lastValue = this->param_11_value;
    }

    this->expr_05_in1_set(v);
}

void param_12_value_set(number v) {
    v = this->param_12_value_constrain(v);
    this->param_12_value = v;
    this->sendParameter(11, false);

    if (this->param_12_value != this->param_12_lastValue) {
        this->getEngine()->presetTouched();
        this->param_12_lastValue = this->param_12_value;
    }

    this->gen_01_PosNegSync_set(v);
}

void param_13_value_set(number v) {
    v = this->param_13_value_constrain(v);
    this->param_13_value = v;
    this->sendParameter(12, false);

    if (this->param_13_value != this->param_13_lastValue) {
        this->getEngine()->presetTouched();
        this->param_13_lastValue = this->param_13_value;
    }

    this->gen_01_termsToAddPerCount_set(v);
}

void param_14_value_set(number v) {
    v = this->param_14_value_constrain(v);
    this->param_14_value = v;
    this->sendParameter(13, false);

    if (this->param_14_value != this->param_14_lastValue) {
        this->getEngine()->presetTouched();
        this->param_14_lastValue = this->param_14_value;
    }

    this->gen_01_cycleCountToSubtract_set(v);
}

void param_15_value_set(number v) {
    v = this->param_15_value_constrain(v);
    this->param_15_value = v;
    this->sendParameter(14, false);

    if (this->param_15_value != this->param_15_lastValue) {
        this->getEngine()->presetTouched();
        this->param_15_lastValue = this->param_15_value;
    }

    this->gen_01_cycleCountToAdd_set(v);
}

void numberobj_01_valin_set(number v) {
    this->numberobj_01_value_set(v);
}

void numberobj_01_format_set(number v) {
    this->numberobj_01_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void adsr_01_mute_bang() {}

void linetilde_01_target_bang() {}

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

Index getNumInputChannels() const {
    return 0;
}

Index getNumOutputChannels() const {
    return 2;
}

void allocateDataRefs() {
    this->gen_01_manageParam->requestSize(10, 1);
    this->gen_01_manageParam->setSampleRate(this->sr);
    this->gen_01_mtof_17_buffer->requestSize(65536, 1);
    this->gen_01_mtof_17_buffer->setSampleRate(this->sr);
    this->gen_01_mtof_19_buffer->requestSize(65536, 1);
    this->gen_01_mtof_19_buffer->setSampleRate(this->sr);
    this->gen_01_mtof_22_buffer->requestSize(65536, 1);
    this->gen_01_mtof_22_buffer->setSampleRate(this->sr);
    this->gen_01_mtof_56_buffer->requestSize(65536, 1);
    this->gen_01_mtof_56_buffer->setSampleRate(this->sr);
    this->gen_01_mtof_75_buffer->requestSize(65536, 1);
    this->gen_01_mtof_75_buffer->setSampleRate(this->sr);
    this->gen_01_manageParam = this->gen_01_manageParam->allocateIfNeeded();

    if (this->manageParam->hasRequestedSize()) {
        if (this->manageParam->wantsFill())
            this->zeroDataRef(this->manageParam);

        this->getEngine()->sendDataRefUpdated(0);
    }

    this->gen_01_mtof_17_buffer = this->gen_01_mtof_17_buffer->allocateIfNeeded();
    this->gen_01_mtof_19_buffer = this->gen_01_mtof_19_buffer->allocateIfNeeded();
    this->gen_01_mtof_22_buffer = this->gen_01_mtof_22_buffer->allocateIfNeeded();
    this->gen_01_mtof_56_buffer = this->gen_01_mtof_56_buffer->allocateIfNeeded();
    this->gen_01_mtof_75_buffer = this->gen_01_mtof_75_buffer->allocateIfNeeded();

    if (this->RNBODefaultMtofLookupTable256->hasRequestedSize()) {
        if (this->RNBODefaultMtofLookupTable256->wantsFill())
            this->fillRNBODefaultMtofLookupTable256(this->RNBODefaultMtofLookupTable256);

        this->getEngine()->sendDataRefUpdated(1);
    }
}

void initializeObjects() {
    this->numberobj_01_init();
    this->gen_01_sampleCount_init();
    this->gen_01_change_13_init();
    this->gen_01_change_14_init();
    this->gen_01_change_15_init();
    this->gen_01_change_16_init();
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());

    {
        this->scheduleParamInit(0, 0);
    }

    {
        this->scheduleParamInit(1, 0);
    }

    {
        this->scheduleParamInit(2, 0);
    }

    {
        this->scheduleParamInit(3, 0);
    }

    {
        this->scheduleParamInit(4, 0);
    }

    {
        this->scheduleParamInit(5, 0);
    }

    {
        this->scheduleParamInit(6, 0);
    }

    {
        this->scheduleParamInit(7, 0);
    }

    {
        this->scheduleParamInit(8, 0);
    }

    {
        this->scheduleParamInit(9, 0);
    }

    {
        this->scheduleParamInit(10, 0);
    }

    {
        this->scheduleParamInit(11, 0);
    }

    {
        this->scheduleParamInit(12, 0);
    }

    {
        this->scheduleParamInit(13, 0);
    }

    {
        this->scheduleParamInit(14, 0);
    }

    this->processParamInitEvents();
}

static number param_01_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void gen_01_PosNeg_set(number v) {
    this->gen_01_PosNeg = v;
}

static number param_02_value_constrain(number v) {
    v = (v > 1000 ? 1000 : (v < 1 ? 1 : v));
    return v;
}

void adsr_01_decay_set(number v) {
    this->adsr_01_decay = v;
}

static number param_03_value_constrain(number v) {
    v = (v > 1000 ? 1000 : (v < 1 ? 1 : v));
    return v;
}

void adsr_01_attack_set(number v) {
    this->adsr_01_attack = v;
}

static number param_04_value_constrain(number v) {
    v = (v > 3 ? 3 : (v < 1 ? 1 : v));
    return v;
}

void gen_01_ocillator_set(number v) {
    this->gen_01_ocillator = v;
}

static number param_05_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void linetilde_01_time_set(number v) {
    this->linetilde_01_time = v;
}

void linetilde_01_segments_set(const list& v) {
    this->linetilde_01_segments = jsCreateListCopy(v);

    if ((bool)(v->length)) {
        if (v->length == 1 && this->linetilde_01_time == 0) {
            this->linetilde_01_activeRamps->length = 0;
            this->linetilde_01_currentValue = v[0];
        } else {
            auto currentTime = this->currentsampletime();
            number lastRampValue = this->linetilde_01_currentValue;
            number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;

            for (Index i = 0; i < this->linetilde_01_activeRamps->length; i += 3) {
                rampEnd = this->linetilde_01_activeRamps[(Index)(i + 2)];

                if (rampEnd > currentTime) {
                    this->linetilde_01_activeRamps[(Index)(i + 2)] = currentTime;
                    number diff = rampEnd - currentTime;
                    number valueDiff = diff * this->linetilde_01_activeRamps[(Index)(i + 1)];
                    lastRampValue = this->linetilde_01_activeRamps[(Index)i] - valueDiff;
                    this->linetilde_01_activeRamps[(Index)i] = lastRampValue;
                    this->linetilde_01_activeRamps->length = i + 3;
                    rampEnd = currentTime;
                } else {
                    lastRampValue = this->linetilde_01_activeRamps[(Index)i];
                }
            }

            if (rampEnd < currentTime) {
                this->linetilde_01_activeRamps->push(lastRampValue);
                this->linetilde_01_activeRamps->push(0);
                this->linetilde_01_activeRamps->push(currentTime);
            }

            number lastRampEnd = currentTime;

            for (Index i = 0; i < v->length; i += 2) {
                number destinationValue = v[(Index)i];
                number inc = 0;
                number rampTimeInSamples;

                if (v->length > i + 1) {
                    rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);

                    if ((bool)(this->linetilde_01_keepramp)) {
                        this->linetilde_01_time_set(v[(Index)(i + 1)]);
                    }
                } else {
                    rampTimeInSamples = this->mstosamps(this->linetilde_01_time);
                }

                if (rampTimeInSamples <= 0) {
                    rampTimeInSamples = 1;
                }

                inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                lastRampEnd += rampTimeInSamples;
                this->linetilde_01_activeRamps->push(destinationValue);
                this->linetilde_01_activeRamps->push(inc);
                this->linetilde_01_activeRamps->push(lastRampEnd);
                lastRampValue = destinationValue;
            }
        }
    }
}

static number param_06_value_constrain(number v) {
    v = (v > 100 ? 100 : (v < 1 ? 1 : v));
    return v;
}

void gen_01_attenuation_set(number v) {
    this->gen_01_attenuation = v;
}

void expr_02_out1_set(number v) {
    this->expr_02_out1 = v;
    this->gen_01_attenuation_set(this->expr_02_out1);
}

void expr_02_in1_set(number in1) {
    this->expr_02_in1 = in1;
    this->expr_02_out1_set(this->expr_02_in1 + this->expr_02_in2);//#map:+_obj-37:1
}

void expr_03_out1_set(number v) {
    this->expr_03_out1 = v;
    this->expr_02_in1_set(this->expr_03_out1);
}

void expr_03_in1_set(number in1) {
    this->expr_03_in1 = in1;

    this->expr_03_out1_set(
        (this->expr_03_in2 == 0 ? 0 : (this->expr_03_in2 == 0. ? 0. : this->expr_03_in1 / this->expr_03_in2))
    );//#map:/_obj-36:1
}

void expr_04_out1_set(number v) {
    this->expr_04_out1 = v;
    this->expr_03_in1_set(this->expr_04_out1);
}

void expr_04_in1_set(number in1) {
    this->expr_04_in1 = in1;
    this->expr_04_out1_set(fixnan(rnbo_pow(this->expr_04_in1, this->expr_04_in2)));//#map:pow_obj-31:1
}

static number param_07_value_constrain(number v) {
    v = (v > 40 ? 40 : (v < 2 ? 2 : v));
    return v;
}

void gen_01_cutoffOvertone_set(number v) {
    this->gen_01_cutoffOvertone = v;
}

static number param_08_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void gen_01_filterOnOff_set(number v) {
    this->gen_01_filterOnOff = v;
}

static number param_09_value_constrain(number v) {
    v = (v > 40 ? 40 : (v < 1 ? 1 : v));
    return v;
}

void gen_01_terms_set(number v) {
    this->gen_01_terms = v;
}

static number param_10_value_constrain(number v) {
    v = (v > 5000 ? 5000 : (v < 0 ? 0 : v));
    return v;
}

void adsr_01_release_set(number v) {
    this->adsr_01_release = v;
}

static number param_11_value_constrain(number v) {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

void adsr_01_sustain_set(number v) {
    this->adsr_01_sustain = v;
}

void expr_05_out1_set(number v) {
    this->expr_05_out1 = v;
    this->adsr_01_sustain_set(this->expr_05_out1);
}

void expr_05_in1_set(number in1) {
    this->expr_05_in1 = in1;

    this->expr_05_out1_set(
        (this->expr_05_in2 == 0 ? 0 : (this->expr_05_in2 == 0. ? 0. : this->expr_05_in1 / this->expr_05_in2))
    );//#map:/_obj-43:1
}

static number param_12_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void gen_01_PosNegSync_set(number v) {
    this->gen_01_PosNegSync = v;
}

static number param_13_value_constrain(number v) {
    v = (v > 20 ? 20 : (v < 1 ? 1 : v));
    return v;
}

void gen_01_termsToAddPerCount_set(number v) {
    this->gen_01_termsToAddPerCount = v;
}

static number param_14_value_constrain(number v) {
    v = (v > 20 ? 20 : (v < 0 ? 0 : v));
    return v;
}

void gen_01_cycleCountToSubtract_set(number v) {
    this->gen_01_cycleCountToSubtract = v;
}

static number param_15_value_constrain(number v) {
    v = (v > 20 ? 20 : (v < 0 ? 0 : v));
    return v;
}

void gen_01_cycleCountToAdd_set(number v) {
    this->gen_01_cycleCountToAdd = v;
}

void gen_01_in1_set(number v) {
    this->gen_01_in1 = v;
}

void numberobj_01_output_set(number v) {
    this->gen_01_in1_set(v);
}

void numberobj_01_value_set(number v) {
    this->numberobj_01_value_setter(v);
    v = this->numberobj_01_value;
    number localvalue = v;

    if (this->numberobj_01_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-26"), localvalue, this->_currentTime);
    this->numberobj_01_output_set(localvalue);
}

void notein_01_outchannel_set(number ) {}

void notein_01_releasevelocity_set(number ) {}

void adsr_01_trigger_number_set(number v) {
    this->adsr_01_trigger_number = v;

    if (v != 0)
        this->adsr_01_triggerBuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = 1;

    for (number i = this->sampleOffsetIntoNextAudioBuffer; i < this->vectorsize(); i++) {
        this->adsr_01_triggerValueBuf[(Index)i] = v;
    }
}

void expr_01_out1_set(number v) {
    this->expr_01_out1 = v;
    this->adsr_01_trigger_number_set(this->expr_01_out1);
}

void expr_01_in1_set(number in1) {
    this->expr_01_in1 = in1;

    this->expr_01_out1_set(
        (this->expr_01_in2 == 0 ? 0 : (this->expr_01_in2 == 0. ? 0. : this->expr_01_in1 / this->expr_01_in2))
    );//#map:/_obj-20:1
}

void notein_01_velocity_set(number v) {
    this->expr_01_in1_set(v);
}

void notein_01_notenumber_set(number v) {
    this->numberobj_01_value_set(v);
}

void notein_01_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (channel == this->notein_01_channel || this->notein_01_channel == 0) {
        if (status == 144 || status == 128) {
            this->notein_01_outchannel_set(channel);

            if (status == 128) {
                this->notein_01_releasevelocity_set(data[2]);
                this->notein_01_velocity_set(0);
            } else {
                this->notein_01_releasevelocity_set(0);
                this->notein_01_velocity_set(data[2]);
            }

            this->notein_01_notenumber_set(data[1]);
        }
    }
}

void gen_01_perform(
    number in1,
    number termsToAddPerCount,
    number cycleCountToSubtract,
    number cycleCountToAdd,
    number PosNegSync,
    number PosNeg,
    number ocillator,
    number attenuation,
    number cutoffOvertone,
    number filterOnOff,
    number terms,
    SampleValue * out1,
    Index n
) {
    auto __gen_01_sampleCount_value = this->gen_01_sampleCount_value;
    Index i0;

    for (i0 = 0; i0 < n; i0++) {
        if (PosNeg == 1) {
            this->poke_default(this->gen_01_manageParam, terms, 0, 0, 0);
            this->poke_default(this->gen_01_manageParam, filterOnOff, 1, 0, 0);
            this->poke_default(this->gen_01_manageParam, cutoffOvertone, 2, 0, 0);
            this->poke_default(this->gen_01_manageParam, attenuation, 3, 0, 0);
            this->poke_default(this->gen_01_manageParam, ocillator, 4, 0, 0);
        } else {
            this->poke_default(this->gen_01_manageParam, terms, 5, 0, 0);
            this->poke_default(this->gen_01_manageParam, filterOnOff, 6, 0, 0);
            this->poke_default(this->gen_01_manageParam, cutoffOvertone, 7, 0, 0);
            this->poke_default(this->gen_01_manageParam, attenuation, 8, 0, 0);
            this->poke_default(this->gen_01_manageParam, ocillator, 9, 0, 0);
        }

        if (PosNegSync == 1) {
            this->poke_default(this->gen_01_manageParam, terms, 0, 0, 0);
            this->poke_default(this->gen_01_manageParam, terms, 5, 0, 0);
            this->poke_default(this->gen_01_manageParam, filterOnOff, 1, 0, 0);
            this->poke_default(this->gen_01_manageParam, filterOnOff, 6, 0, 0);
            this->poke_default(this->gen_01_manageParam, cutoffOvertone, 2, 0, 0);
            this->poke_default(this->gen_01_manageParam, cutoffOvertone, 7, 0, 0);
            this->poke_default(this->gen_01_manageParam, attenuation, 3, 0, 0);
            this->poke_default(this->gen_01_manageParam, attenuation, 8, 0, 0);
            this->poke_default(this->gen_01_manageParam, ocillator, 4, 0, 0);
            this->poke_default(this->gen_01_manageParam, ocillator, 9, 0, 0);
        }

        number posTerms = 0;
        auto result_0 = this->peek_default(this->gen_01_manageParam, 0, 0);
        posTerms = result_0[0];
        number posFilterOnOff = 0;
        auto result_1 = this->peek_default(this->gen_01_manageParam, 1, 0);
        posFilterOnOff = result_1[0];
        number posCutoffOvertone = 0;
        auto result_2 = this->peek_default(this->gen_01_manageParam, 2, 0);
        posCutoffOvertone = result_2[0];
        number posAttenuation = 0;
        auto result_3 = this->peek_default(this->gen_01_manageParam, 3, 0);
        posAttenuation = result_3[0];
        number posOcillator = 0;
        auto result_4 = this->peek_default(this->gen_01_manageParam, 4, 0);
        posOcillator = result_4[0];
        number negTerms = 0;
        auto result_5 = this->peek_default(this->gen_01_manageParam, 5, 0);
        negTerms = result_5[0];
        number negFilterOnOff = 0;
        auto result_6 = this->peek_default(this->gen_01_manageParam, 6, 0);
        negFilterOnOff = result_6[0];
        number negCutoffOvertone = 0;
        auto result_7 = this->peek_default(this->gen_01_manageParam, 7, 0);
        negCutoffOvertone = result_7[0];
        number negAttenuation = 0;
        auto result_8 = this->peek_default(this->gen_01_manageParam, 8, 0);
        negAttenuation = result_8[0];
        number negOcillator = 0;
        auto result_9 = this->peek_default(this->gen_01_manageParam, 9, 0);
        negOcillator = result_9[0];
        number posWave_10 = 0;
        number negWave_11 = 0;
        number countReset_12 = 0;

        if (this->gen_01_change_13_next(cycleCountToAdd) != 0 || this->gen_01_change_14_next(cycleCountToSubtract) != 0 || this->gen_01_change_15_next(terms) != 0 || this->gen_01_change_16_next(this->gen_01_mtof_17_next(in1, 440)) != 0) {
            countReset_12 = 1;
            __gen_01_sampleCount_value = 0;
        }

        number wave_gen_20 = this->gen_01_phasor_18_next(this->gen_01_mtof_19_next(in1, 440), countReset_12);
        auto scaled_wave_21 = this->scale(wave_gen_20, 0, 1, 0, 6.28318530717958647692, 1);
        number periodSamps_23 = (this->gen_01_mtof_22_next(in1, 440) == 0. ? 0. : this->samplerate() / this->gen_01_mtof_22_next(in1, 440));
        __gen_01_sampleCount_value = __gen_01_sampleCount_value + 1;

        auto cycleCount_24 = this->wrap(
            __gen_01_sampleCount_value,
            0,
            periodSamps_23 * (cycleCountToAdd + cycleCountToSubtract)
        );

        number cycleCount_1_25 = this->intnum((periodSamps_23 == 0. ? 0. : cycleCount_24 / periodSamps_23)) + 1;

        if (cycleCountToAdd != 0 && cycleCount_1_25 <= cycleCountToAdd) {
            number peek_2 = 0;
            number peek_3 = 0;
            auto result_26 = this->peek_default(this->gen_01_manageParam, 0, 0);
            peek_3 = result_26[1];
            peek_2 = result_26[0];
            posTerms = peek_2 + cycleCount_1_25 * termsToAddPerCount;
            number peek_4 = 0;
            number peek_5 = 0;
            auto result_27 = this->peek_default(this->gen_01_manageParam, 5, 0);
            peek_5 = result_27[1];
            peek_4 = result_27[0];
            negTerms = peek_4 + cycleCount_1_25 * termsToAddPerCount;
        } else if (cycleCountToAdd != 0 && cycleCount_1_25 > cycleCountToAdd) {
            number totalAddedTerms_28 = cycleCountToAdd * termsToAddPerCount;
            number termsToSubtractPerCount_29 = (cycleCountToSubtract == 0. ? 0. : totalAddedTerms_28 / cycleCountToSubtract);
            number countForSubtract_30 = cycleCount_1_25 - cycleCountToAdd;
            auto addedTerms_31 = this->intnum(totalAddedTerms_28 - termsToSubtractPerCount_29 * countForSubtract_30);
            number peek_6 = 0;
            number peek_7 = 0;
            auto result_32 = this->peek_default(this->gen_01_manageParam, 0, 0);
            peek_7 = result_32[1];
            peek_6 = result_32[0];
            posTerms = peek_6 + addedTerms_31;
            number peek_8 = 0;
            number peek_9 = 0;
            auto result_33 = this->peek_default(this->gen_01_manageParam, 5, 0);
            peek_9 = result_33[1];
            peek_8 = result_33[0];
            negTerms = peek_8 + addedTerms_31;
        } else {
            auto result_34 = this->peek_default(this->gen_01_manageParam, 0, 0);
            posTerms = result_34[0];
            auto result_35 = this->peek_default(this->gen_01_manageParam, 5, 0);
            negTerms = result_35[0];
        }

        auto maxTerms_36 = this->maximum(posTerms, negTerms);

        for (number i = 1; i <= maxTerms_36; i = i + 1) {
            number sine_wave1_37 = rnbo_sin(scaled_wave_21 * i);

            if (i <= posTerms) {
                number processSynthesis_38 = 0;

                {
                    auto Ocillator_44 = posOcillator;
                    auto Attenuation_43 = posAttenuation;
                    auto CutoffOvertone_42 = posCutoffOvertone;
                    auto FilterOnOff_41 = posFilterOnOff;
                    auto index_40 = i;
                    auto inputFreq_39 = in1;
                    number Factors_45 = 1;
                    number Amp_filter_46 = 1;

                    if (Ocillator_44 == 1) {
                        if (this->safemod(index_40, 2) == 1) {
                            Factors_45 = (3.14159265358979323846 * index_40 == 0. ? 0. : (number)4 / (3.14159265358979323846 * index_40));
                        } else {
                            Factors_45 = 0;
                        }
                    } else if (Ocillator_44 == 2) {
                        if (this->safemod(index_40, 2) == 1) {
                            number myTriangle_47 = 0;

                            {
                                auto n2_48 = index_40;
                                number amp_factor2_49 = (fixnan(rnbo_pow(3.14159265358979323846, 2)) * fixnan(rnbo_pow(n2_48, 2)) == 0. ? 0. : (number)8 / (fixnan(rnbo_pow(3.14159265358979323846, 2)) * fixnan(rnbo_pow(n2_48, 2))));
                                number phase_factor2_50 = fixnan(rnbo_pow(-1, (n2_48 - 1) / (number)2));
                                myTriangle_47 = amp_factor2_49 * phase_factor2_50;
                            }

                            Factors_45 = myTriangle_47;
                        } else {
                            Factors_45 = 0;
                        }
                    } else {
                        number mySawtooth_51 = 0;

                        {
                            auto n3_52 = index_40;
                            number amp_factor3_53 = (3.14159265358979323846 * n3_52 == 0. ? 0. : (number)2 / (3.14159265358979323846 * n3_52));
                            number phase_factor3_54 = fixnan(rnbo_pow(-1, n3_52 + 1));
                            mySawtooth_51 = amp_factor3_53 * phase_factor3_54;
                        }

                        Factors_45 = mySawtooth_51;
                    }

                    if (FilterOnOff_41 == 1) {
                        if (index_40 >= CutoffOvertone_42) {
                            number n_overtone_55 = (index_40 - CutoffOvertone_42 + 1) * Attenuation_43;
                            Amp_filter_46 = (n_overtone_55 == 0. ? 0. : (number)1 / n_overtone_55);
                        }
                    }

                    if (this->gen_01_mtof_56_next(inputFreq_39, 440) * index_40 > this->samplerate() / (number)2) {
                        Factors_45 = 0;
                    }

                    processSynthesis_38 = Factors_45 * Amp_filter_46;
                }

                posWave_10 = posWave_10 + sine_wave1_37 * processSynthesis_38;
            }

            if (i <= negTerms) {
                number processSynthesis_57 = 0;

                {
                    auto Ocillator_63 = negOcillator;
                    auto Attenuation_62 = negAttenuation;
                    auto CutoffOvertone_61 = negCutoffOvertone;
                    auto FilterOnOff_60 = negFilterOnOff;
                    auto index_59 = i;
                    auto inputFreq_58 = in1;
                    number Factors_64 = 1;
                    number Amp_filter_65 = 1;

                    if (Ocillator_63 == 1) {
                        if (this->safemod(index_59, 2) == 1) {
                            Factors_64 = (3.14159265358979323846 * index_59 == 0. ? 0. : (number)4 / (3.14159265358979323846 * index_59));
                        } else {
                            Factors_64 = 0;
                        }
                    } else if (Ocillator_63 == 2) {
                        if (this->safemod(index_59, 2) == 1) {
                            number myTriangle_66 = 0;

                            {
                                auto n2_67 = index_59;
                                number amp_factor2_68 = (fixnan(rnbo_pow(3.14159265358979323846, 2)) * fixnan(rnbo_pow(n2_67, 2)) == 0. ? 0. : (number)8 / (fixnan(rnbo_pow(3.14159265358979323846, 2)) * fixnan(rnbo_pow(n2_67, 2))));
                                number phase_factor2_69 = fixnan(rnbo_pow(-1, (n2_67 - 1) / (number)2));
                                myTriangle_66 = amp_factor2_68 * phase_factor2_69;
                            }

                            Factors_64 = myTriangle_66;
                        } else {
                            Factors_64 = 0;
                        }
                    } else {
                        number mySawtooth_70 = 0;

                        {
                            auto n3_71 = index_59;
                            number amp_factor3_72 = (3.14159265358979323846 * n3_71 == 0. ? 0. : (number)2 / (3.14159265358979323846 * n3_71));
                            number phase_factor3_73 = fixnan(rnbo_pow(-1, n3_71 + 1));
                            mySawtooth_70 = amp_factor3_72 * phase_factor3_73;
                        }

                        Factors_64 = mySawtooth_70;
                    }

                    if (FilterOnOff_60 == 1) {
                        if (index_59 >= CutoffOvertone_61) {
                            number n_overtone_74 = (index_59 - CutoffOvertone_61 + 1) * Attenuation_62;
                            Amp_filter_65 = (n_overtone_74 == 0. ? 0. : (number)1 / n_overtone_74);
                        }
                    }

                    if (this->gen_01_mtof_75_next(inputFreq_58, 440) * index_59 > this->samplerate() / (number)2) {
                        Factors_64 = 0;
                    }

                    processSynthesis_57 = Factors_64 * Amp_filter_65;
                }

                negWave_11 = negWave_11 + sine_wave1_37 * processSynthesis_57;
            }
        }

        if (posWave_10 >= 0) {
            negWave_11 = negWave_11 * 0;
        } else {
            posWave_10 = posWave_10 * 0;
        }

        number SynthesizedWave_10_76 = negWave_11 + posWave_10;
        number expr_11_77 = (SynthesizedWave_10_76 * 0.7 > 1 ? 1 : (SynthesizedWave_10_76 * 0.7 < -1 ? -1 : SynthesizedWave_10_76 * 0.7));
        out1[(Index)i0] = expr_11_77;
    }

    this->gen_01_sampleCount_value = __gen_01_sampleCount_value;
}

void adsr_01_perform(
    number attack,
    number decay,
    number sustain,
    number release,
    const SampleValue * trigger_signal,
    SampleValue * out,
    Index n
) {
    RNBO_UNUSED(trigger_signal);
    auto __adsr_01_trigger_number = this->adsr_01_trigger_number;
    auto __adsr_01_time = this->adsr_01_time;
    auto __adsr_01_amplitude = this->adsr_01_amplitude;
    auto __adsr_01_outval = this->adsr_01_outval;
    auto __adsr_01_startingpoint = this->adsr_01_startingpoint;
    auto __adsr_01_phase = this->adsr_01_phase;
    auto __adsr_01_legato = this->adsr_01_legato;
    auto __adsr_01_lastTriggerVal = this->adsr_01_lastTriggerVal;
    auto __adsr_01_mspersamp = this->adsr_01_mspersamp;
    bool bangMute = false;

    for (Index i = 0; i < n; i++) {
        number clampedattack = (attack > __adsr_01_mspersamp ? attack : __adsr_01_mspersamp);
        number clampeddecay = (decay > __adsr_01_mspersamp ? decay : __adsr_01_mspersamp);
        number clampedrelease = (release > __adsr_01_mspersamp ? release : __adsr_01_mspersamp);
        number currentTriggerVal = this->adsr_01_triggerValueBuf[(Index)i];

        if ((__adsr_01_lastTriggerVal == 0.0 && currentTriggerVal != 0.0) || this->adsr_01_triggerBuf[(Index)i] == 1) {
            if ((bool)(__adsr_01_legato)) {
                if (__adsr_01_phase != 0) {
                    __adsr_01_startingpoint = __adsr_01_outval;
                } else {
                    __adsr_01_startingpoint = 0;
                }
            } else {
                __adsr_01_startingpoint = 0;
            }

            __adsr_01_amplitude = currentTriggerVal;
            __adsr_01_phase = 1;
            __adsr_01_time = 0.0;
            bangMute = false;
        } else if (__adsr_01_lastTriggerVal != 0.0 && currentTriggerVal == 0.0) {
            if (__adsr_01_phase != 4 && __adsr_01_phase != 0) {
                __adsr_01_phase = 4;
                __adsr_01_amplitude = __adsr_01_outval;
                __adsr_01_time = 0.0;
            }
        }

        __adsr_01_time += __adsr_01_mspersamp;

        if (__adsr_01_phase == 0) {
            __adsr_01_outval = 0;
        } else if (__adsr_01_phase == 1) {
            if (__adsr_01_time > clampedattack) {
                __adsr_01_time -= clampedattack;
                __adsr_01_phase = 2;
                __adsr_01_outval = __adsr_01_amplitude;
            } else {
                __adsr_01_outval = (__adsr_01_amplitude - __adsr_01_startingpoint) * __adsr_01_time / clampedattack + __adsr_01_startingpoint;
            }
        } else if (__adsr_01_phase == 2) {
            if (__adsr_01_time > clampeddecay) {
                __adsr_01_time -= clampeddecay;
                __adsr_01_phase = 3;
                __adsr_01_outval = __adsr_01_amplitude * sustain;
            } else {
                __adsr_01_outval = __adsr_01_amplitude * sustain + (__adsr_01_amplitude - __adsr_01_amplitude * sustain) * (1. - __adsr_01_time / clampeddecay);
            }
        } else if (__adsr_01_phase == 3) {
            __adsr_01_outval = __adsr_01_amplitude * sustain;
        } else if (__adsr_01_phase == 4) {
            if (__adsr_01_time > clampedrelease) {
                __adsr_01_time = 0;
                __adsr_01_phase = 0;
                __adsr_01_outval = 0;
                __adsr_01_amplitude = 0;
                bangMute = true;
            } else {
                __adsr_01_outval = __adsr_01_amplitude * (1.0 - __adsr_01_time / clampedrelease);
            }
        }

        out[(Index)i] = __adsr_01_outval;
        this->adsr_01_triggerBuf[(Index)i] = 0;
        this->adsr_01_triggerValueBuf[(Index)i] = __adsr_01_trigger_number;
        __adsr_01_lastTriggerVal = currentTriggerVal;
    }

    if ((bool)(bangMute)) {
        this->getEngine()->scheduleClockEventWithValue(
            this,
            -1468824490,
            this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
            0
        );;
    }

    this->adsr_01_lastTriggerVal = __adsr_01_lastTriggerVal;
    this->adsr_01_phase = __adsr_01_phase;
    this->adsr_01_startingpoint = __adsr_01_startingpoint;
    this->adsr_01_outval = __adsr_01_outval;
    this->adsr_01_amplitude = __adsr_01_amplitude;
    this->adsr_01_time = __adsr_01_time;
}

void rampsmooth_tilde_01_perform(const Sample * x, number up, number down, SampleValue * out1, Index n) {
    RNBO_UNUSED(down);
    RNBO_UNUSED(up);
    auto __rampsmooth_tilde_01_increment = this->rampsmooth_tilde_01_increment;
    auto __rampsmooth_tilde_01_index = this->rampsmooth_tilde_01_index;
    auto __rampsmooth_tilde_01_prev = this->rampsmooth_tilde_01_prev;
    Index i;

    for (i = 0; i < n; i++) {
        if (this->rampsmooth_tilde_01_d_next(x[(Index)i]) != 0.) {
            if (x[(Index)i] > __rampsmooth_tilde_01_prev) {
                number _up = 100;

                if (_up < 1)
                    _up = 1;

                __rampsmooth_tilde_01_index = _up;
                __rampsmooth_tilde_01_increment = (x[(Index)i] - __rampsmooth_tilde_01_prev) / _up;
            } else if (x[(Index)i] < __rampsmooth_tilde_01_prev) {
                number _down = 100;

                if (_down < 1)
                    _down = 1;

                __rampsmooth_tilde_01_index = _down;
                __rampsmooth_tilde_01_increment = (x[(Index)i] - __rampsmooth_tilde_01_prev) / _down;
            }
        }

        if (__rampsmooth_tilde_01_index > 0) {
            __rampsmooth_tilde_01_prev += __rampsmooth_tilde_01_increment;
            __rampsmooth_tilde_01_index -= 1;
        } else {
            __rampsmooth_tilde_01_prev = x[(Index)i];
        }

        out1[(Index)i] = __rampsmooth_tilde_01_prev;
    }

    this->rampsmooth_tilde_01_prev = __rampsmooth_tilde_01_prev;
    this->rampsmooth_tilde_01_index = __rampsmooth_tilde_01_index;
    this->rampsmooth_tilde_01_increment = __rampsmooth_tilde_01_increment;
}

void dspexpr_02_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void linetilde_01_perform(SampleValue * out, Index n) {
    auto __linetilde_01_time = this->linetilde_01_time;
    auto __linetilde_01_keepramp = this->linetilde_01_keepramp;
    auto __linetilde_01_currentValue = this->linetilde_01_currentValue;
    Index i = 0;

    if ((bool)(this->linetilde_01_activeRamps->length)) {
        while ((bool)(this->linetilde_01_activeRamps->length) && i < n) {
            number destinationValue = this->linetilde_01_activeRamps[0];
            number inc = this->linetilde_01_activeRamps[1];
            number rampTimeInSamples = this->linetilde_01_activeRamps[2] - this->audioProcessSampleCount - i;
            number val = __linetilde_01_currentValue;

            while (rampTimeInSamples > 0 && i < n) {
                out[(Index)i] = val;
                val += inc;
                i++;
                rampTimeInSamples--;
            }

            if (rampTimeInSamples <= 0) {
                val = destinationValue;
                this->linetilde_01_activeRamps->splice(0, 3);

                if ((bool)(!(bool)(this->linetilde_01_activeRamps->length))) {
                    this->getEngine()->scheduleClockEventWithValue(
                        this,
                        -62043057,
                        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                        0
                    );;

                    if ((bool)(!(bool)(__linetilde_01_keepramp))) {
                        __linetilde_01_time = 0;
                    }
                }
            }

            __linetilde_01_currentValue = val;
        }
    }

    while (i < n) {
        out[(Index)i] = __linetilde_01_currentValue;
        i++;
    }

    this->linetilde_01_currentValue = __linetilde_01_currentValue;
    this->linetilde_01_time = __linetilde_01_time;
}

void dspexpr_01_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void signalforwarder_01_perform(const SampleValue * input, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input[(Index)i];
    }
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void numberobj_01_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_01_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_01_value = localvalue;
}

void numberobj_01_init() {
    this->numberobj_01_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-26"), 1, this->_currentTime);
}

void numberobj_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_01_value;
}

void numberobj_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_01_value_set(preset["value"]);
}

number gen_01_sampleCount_getvalue() {
    return this->gen_01_sampleCount_value;
}

void gen_01_sampleCount_setvalue(number val) {
    this->gen_01_sampleCount_value = val;
}

void gen_01_sampleCount_reset() {
    this->gen_01_sampleCount_value = 0;
}

void gen_01_sampleCount_init() {
    this->gen_01_sampleCount_value = 0;
}

number gen_01_change_13_next(number x) {
    number temp = x - this->gen_01_change_13_prev;
    this->gen_01_change_13_prev = x;
    return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
}

void gen_01_change_13_init() {
    this->gen_01_change_13_prev = 0;
}

void gen_01_change_13_reset() {
    this->gen_01_change_13_prev = 0;
}

number gen_01_change_14_next(number x) {
    number temp = x - this->gen_01_change_14_prev;
    this->gen_01_change_14_prev = x;
    return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
}

void gen_01_change_14_init() {
    this->gen_01_change_14_prev = 0;
}

void gen_01_change_14_reset() {
    this->gen_01_change_14_prev = 0;
}

number gen_01_change_15_next(number x) {
    number temp = x - this->gen_01_change_15_prev;
    this->gen_01_change_15_prev = x;
    return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
}

void gen_01_change_15_init() {
    this->gen_01_change_15_prev = 0;
}

void gen_01_change_15_reset() {
    this->gen_01_change_15_prev = 0;
}

number gen_01_change_16_next(number x) {
    number temp = x - this->gen_01_change_16_prev;
    this->gen_01_change_16_prev = x;
    return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
}

void gen_01_change_16_init() {
    this->gen_01_change_16_prev = 0;
}

void gen_01_change_16_reset() {
    this->gen_01_change_16_prev = 0;
}

number gen_01_mtof_17_next(number midivalue, number tuning) {
    RNBO_UNUSED(tuning);

    if (midivalue == this->gen_01_mtof_17_lastInValue && 440 == this->gen_01_mtof_17_lastTuning)
        return this->gen_01_mtof_17_lastOutValue;

    this->gen_01_mtof_17_lastInValue = midivalue;
    this->gen_01_mtof_17_lastTuning = 440;
    number result = 0;

    {
        result = rnbo_exp(.057762265 * (midivalue - 69.0));
    }

    this->gen_01_mtof_17_lastOutValue = 440 * result;
    return this->gen_01_mtof_17_lastOutValue;
}

void gen_01_mtof_17_reset() {
    this->gen_01_mtof_17_lastInValue = 0;
    this->gen_01_mtof_17_lastOutValue = 0;
    this->gen_01_mtof_17_lastTuning = 0;
}

number gen_01_phasor_18_next(number freq, number reset) {
    {
        {
            if (reset > 0.)
                this->gen_01_phasor_18_currentPhase = 0;
        }
    }

    number pincr = freq * this->gen_01_phasor_18_conv;

    if (this->gen_01_phasor_18_currentPhase < 0.)
        this->gen_01_phasor_18_currentPhase = 1. + this->gen_01_phasor_18_currentPhase;

    if (this->gen_01_phasor_18_currentPhase > 1.)
        this->gen_01_phasor_18_currentPhase = this->gen_01_phasor_18_currentPhase - 1.;

    number tmp = this->gen_01_phasor_18_currentPhase;
    this->gen_01_phasor_18_currentPhase += pincr;
    return tmp;
}

void gen_01_phasor_18_reset() {
    this->gen_01_phasor_18_currentPhase = 0;
}

void gen_01_phasor_18_dspsetup() {
    this->gen_01_phasor_18_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

number gen_01_mtof_19_next(number midivalue, number tuning) {
    RNBO_UNUSED(tuning);

    if (midivalue == this->gen_01_mtof_19_lastInValue && 440 == this->gen_01_mtof_19_lastTuning)
        return this->gen_01_mtof_19_lastOutValue;

    this->gen_01_mtof_19_lastInValue = midivalue;
    this->gen_01_mtof_19_lastTuning = 440;
    number result = 0;

    {
        result = rnbo_exp(.057762265 * (midivalue - 69.0));
    }

    this->gen_01_mtof_19_lastOutValue = 440 * result;
    return this->gen_01_mtof_19_lastOutValue;
}

void gen_01_mtof_19_reset() {
    this->gen_01_mtof_19_lastInValue = 0;
    this->gen_01_mtof_19_lastOutValue = 0;
    this->gen_01_mtof_19_lastTuning = 0;
}

number gen_01_mtof_22_next(number midivalue, number tuning) {
    RNBO_UNUSED(tuning);

    if (midivalue == this->gen_01_mtof_22_lastInValue && 440 == this->gen_01_mtof_22_lastTuning)
        return this->gen_01_mtof_22_lastOutValue;

    this->gen_01_mtof_22_lastInValue = midivalue;
    this->gen_01_mtof_22_lastTuning = 440;
    number result = 0;

    {
        result = rnbo_exp(.057762265 * (midivalue - 69.0));
    }

    this->gen_01_mtof_22_lastOutValue = 440 * result;
    return this->gen_01_mtof_22_lastOutValue;
}

void gen_01_mtof_22_reset() {
    this->gen_01_mtof_22_lastInValue = 0;
    this->gen_01_mtof_22_lastOutValue = 0;
    this->gen_01_mtof_22_lastTuning = 0;
}

number gen_01_mtof_56_next(number midivalue, number tuning) {
    RNBO_UNUSED(tuning);

    if (midivalue == this->gen_01_mtof_56_lastInValue && 440 == this->gen_01_mtof_56_lastTuning)
        return this->gen_01_mtof_56_lastOutValue;

    this->gen_01_mtof_56_lastInValue = midivalue;
    this->gen_01_mtof_56_lastTuning = 440;
    number result = 0;

    {
        result = rnbo_exp(.057762265 * (midivalue - 69.0));
    }

    this->gen_01_mtof_56_lastOutValue = 440 * result;
    return this->gen_01_mtof_56_lastOutValue;
}

void gen_01_mtof_56_reset() {
    this->gen_01_mtof_56_lastInValue = 0;
    this->gen_01_mtof_56_lastOutValue = 0;
    this->gen_01_mtof_56_lastTuning = 0;
}

number gen_01_mtof_75_next(number midivalue, number tuning) {
    RNBO_UNUSED(tuning);

    if (midivalue == this->gen_01_mtof_75_lastInValue && 440 == this->gen_01_mtof_75_lastTuning)
        return this->gen_01_mtof_75_lastOutValue;

    this->gen_01_mtof_75_lastInValue = midivalue;
    this->gen_01_mtof_75_lastTuning = 440;
    number result = 0;

    {
        result = rnbo_exp(.057762265 * (midivalue - 69.0));
    }

    this->gen_01_mtof_75_lastOutValue = 440 * result;
    return this->gen_01_mtof_75_lastOutValue;
}

void gen_01_mtof_75_reset() {
    this->gen_01_mtof_75_lastInValue = 0;
    this->gen_01_mtof_75_lastOutValue = 0;
    this->gen_01_mtof_75_lastTuning = 0;
}

void gen_01_dspsetup(bool force) {
    if ((bool)(this->gen_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gen_01_setupDone = true;
    this->gen_01_phasor_18_dspsetup();
}

number rampsmooth_tilde_01_d_next(number x) {
    number temp = (number)(x - this->rampsmooth_tilde_01_d_prev);
    this->rampsmooth_tilde_01_d_prev = x;
    return temp;
}

void rampsmooth_tilde_01_d_dspsetup() {
    this->rampsmooth_tilde_01_d_reset();
}

void rampsmooth_tilde_01_d_reset() {
    this->rampsmooth_tilde_01_d_prev = 0;
}

void rampsmooth_tilde_01_dspsetup(bool force) {
    if ((bool)(this->rampsmooth_tilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->rampsmooth_tilde_01_setupDone = true;
    this->rampsmooth_tilde_01_d_dspsetup();
}

void adsr_01_dspsetup(bool force) {
    if ((bool)(this->adsr_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->adsr_01_mspersamp = (number)1000 / this->sr;
    this->adsr_01_setupDone = true;
}

void param_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_01_value;
}

void param_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_01_value_set(preset["value"]);
}

void param_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_02_value;
}

void param_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_02_value_set(preset["value"]);
}

void param_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_03_value;
}

void param_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_03_value_set(preset["value"]);
}

void param_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_04_value;
}

void param_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_04_value_set(preset["value"]);
}

void param_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_05_value;
}

void param_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_05_value_set(preset["value"]);
}

void param_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_06_value;
}

void param_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_06_value_set(preset["value"]);
}

void param_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_07_value;
}

void param_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_07_value_set(preset["value"]);
}

void param_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_08_value;
}

void param_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_08_value_set(preset["value"]);
}

void param_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_09_value;
}

void param_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_09_value_set(preset["value"]);
}

void param_10_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_10_value;
}

void param_10_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_10_value_set(preset["value"]);
}

void param_11_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_11_value;
}

void param_11_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_11_value_set(preset["value"]);
}

void param_12_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_12_value;
}

void param_12_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_12_value_set(preset["value"]);
}

void param_13_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_13_value;
}

void param_13_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_13_value_set(preset["value"]);
}

void param_14_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_14_value;
}

void param_14_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_14_value_set(preset["value"]);
}

void param_15_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_15_value;
}

void param_15_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_15_value_set(preset["value"]);
}

Index globaltransport_getSampleOffset(MillisecondTime time) {
    return this->mstosamps(this->maximum(0, time - this->getEngine()->getCurrentTime()));
}

number globaltransport_getTempoAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < this->vs ? this->globaltransport_tempo[(Index)sampleOffset] : this->globaltransport_lastTempo);
}

number globaltransport_getStateAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < this->vs ? this->globaltransport_state[(Index)sampleOffset] : this->globaltransport_lastState);
}

number globaltransport_getState(MillisecondTime time) {
    return this->globaltransport_getStateAtSample(this->globaltransport_getSampleOffset(time));
}

number globaltransport_getBeatTime(MillisecondTime time) {
    number i = 2;

    while (i < this->globaltransport_beatTimeChanges->length && this->globaltransport_beatTimeChanges[(Index)(i + 1)] <= time) {
        i += 2;
    }

    i -= 2;
    number beatTimeBase = this->globaltransport_beatTimeChanges[(Index)i];

    if (this->globaltransport_getState(time) == 0)
        return beatTimeBase;

    number beatTimeBaseMsTime = this->globaltransport_beatTimeChanges[(Index)(i + 1)];
    number diff = time - beatTimeBaseMsTime;
    return beatTimeBase + this->mstobeats(diff);
}

bool globaltransport_setTempo(MillisecondTime time, number tempo, bool notify) {
    if ((bool)(notify)) {
        this->processTempoEvent(time, tempo);
        this->globaltransport_notify = true;
    } else {
        Index offset = (Index)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getTempoAtSample(offset) != tempo) {
            this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
            this->globaltransport_beatTimeChanges->push(time);
            fillSignal(this->globaltransport_tempo, this->vs, tempo, offset);
            this->globaltransport_lastTempo = tempo;
            this->globaltransport_tempoNeedsReset = true;
            return true;
        }
    }

    return false;
}

number globaltransport_getTempo(MillisecondTime time) {
    return this->globaltransport_getTempoAtSample(this->globaltransport_getSampleOffset(time));
}

bool globaltransport_setState(MillisecondTime time, number state, bool notify) {
    if ((bool)(notify)) {
        this->processTransportEvent(time, TransportState(state));
        this->globaltransport_notify = true;
    } else {
        Index offset = (Index)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getStateAtSample(offset) != state) {
            fillSignal(this->globaltransport_state, this->vs, state, offset);
            this->globaltransport_lastState = TransportState(state);
            this->globaltransport_stateNeedsReset = true;

            if (state == 0) {
                this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
                this->globaltransport_beatTimeChanges->push(time);
            }

            return true;
        }
    }

    return false;
}

bool globaltransport_setBeatTime(MillisecondTime time, number beattime, bool notify) {
    if ((bool)(notify)) {
        this->processBeatTimeEvent(time, beattime);
        this->globaltransport_notify = true;
        return false;
    } else {
        bool beatTimeHasChanged = false;
        float oldBeatTime = (float)(this->globaltransport_getBeatTime(time));
        float newBeatTime = (float)(beattime);

        if (oldBeatTime != newBeatTime) {
            beatTimeHasChanged = true;
        }

        this->globaltransport_beatTimeChanges->push(beattime);
        this->globaltransport_beatTimeChanges->push(time);
        return beatTimeHasChanged;
    }
}

number globaltransport_getBeatTimeAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getBeatTime(this->getEngine()->getCurrentTime() + msOffset);
}

array<number, 2> globaltransport_getTimeSignature(MillisecondTime time) {
    number i = 3;

    while (i < this->globaltransport_timeSignatureChanges->length && this->globaltransport_timeSignatureChanges[(Index)(i + 2)] <= time) {
        i += 3;
    }

    i -= 3;

    return {
        this->globaltransport_timeSignatureChanges[(Index)i],
        this->globaltransport_timeSignatureChanges[(Index)(i + 1)]
    };
}

array<number, 2> globaltransport_getTimeSignatureAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getTimeSignature(this->getEngine()->getCurrentTime() + msOffset);
}

bool globaltransport_setTimeSignature(MillisecondTime time, number numerator, number denominator, bool notify) {
    if ((bool)(notify)) {
        this->processTimeSignatureEvent(time, (int)(numerator), (int)(denominator));
        this->globaltransport_notify = true;
    } else {
        array<number, 2> currentSig = this->globaltransport_getTimeSignature(time);

        if (currentSig[0] != numerator || currentSig[1] != denominator) {
            this->globaltransport_timeSignatureChanges->push(numerator);
            this->globaltransport_timeSignatureChanges->push(denominator);
            this->globaltransport_timeSignatureChanges->push(time);
            return true;
        }
    }

    return false;
}

void globaltransport_advance() {
    if ((bool)(this->globaltransport_tempoNeedsReset)) {
        fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
        this->globaltransport_tempoNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTempoEvent(this->globaltransport_lastTempo);
        }
    }

    if ((bool)(this->globaltransport_stateNeedsReset)) {
        fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
        this->globaltransport_stateNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTransportEvent(TransportState(this->globaltransport_lastState));
        }
    }

    if (this->globaltransport_beatTimeChanges->length > 2) {
        this->globaltransport_beatTimeChanges[0] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 2)];
        this->globaltransport_beatTimeChanges[1] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 1)];
        this->globaltransport_beatTimeChanges->length = 2;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendBeatTimeEvent(this->globaltransport_beatTimeChanges[0]);
        }
    }

    if (this->globaltransport_timeSignatureChanges->length > 3) {
        this->globaltransport_timeSignatureChanges[0] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 3)];
        this->globaltransport_timeSignatureChanges[1] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 2)];
        this->globaltransport_timeSignatureChanges[2] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 1)];
        this->globaltransport_timeSignatureChanges->length = 3;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTimeSignatureEvent(
                (int)(this->globaltransport_timeSignatureChanges[0]),
                (int)(this->globaltransport_timeSignatureChanges[1])
            );
        }
    }

    this->globaltransport_notify = false;
}

void globaltransport_dspsetup(bool force) {
    if ((bool)(this->globaltransport_setupDone) && (bool)(!(bool)(force)))
        return;

    fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
    this->globaltransport_tempoNeedsReset = false;
    fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
    this->globaltransport_stateNeedsReset = false;
    this->globaltransport_setupDone = true;
}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

void updateTime(MillisecondTime time) {
    this->_currentTime = time;
    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));

    if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;

    if (this->sampleOffsetIntoNextAudioBuffer < 0)
        this->sampleOffsetIntoNextAudioBuffer = 0;
}

void assign_defaults()
{
    numberobj_01_value = 0;
    numberobj_01_value_setter(numberobj_01_value);
    dspexpr_01_in1 = 0;
    dspexpr_01_in2 = 1;
    dspexpr_02_in1 = 0;
    dspexpr_02_in2 = 1;
    notein_01_channel = 0;
    gen_01_in1 = 0;
    gen_01_termsToAddPerCount = 0;
    gen_01_cycleCountToSubtract = 0;
    gen_01_cycleCountToAdd = 0;
    gen_01_PosNegSync = 0;
    gen_01_PosNeg = 0;
    gen_01_ocillator = 0;
    gen_01_attenuation = 0;
    gen_01_cutoffOvertone = 0;
    gen_01_filterOnOff = 0;
    gen_01_terms = 0;
    rampsmooth_tilde_01_x = 0;
    rampsmooth_tilde_01_up = 100;
    rampsmooth_tilde_01_down = 100;
    adsr_01_trigger_number = 0;
    adsr_01_attack = 0;
    adsr_01_decay = 0;
    adsr_01_sustain = 0;
    adsr_01_release = 0;
    adsr_01_legato = 0;
    expr_01_in1 = 0;
    expr_01_in2 = 127;
    expr_01_out1 = 0;
    linetilde_01_time = 10;
    linetilde_01_keepramp = 1;
    param_01_value = 0;
    param_02_value = 100;
    param_03_value = 10;
    param_04_value = 1;
    expr_02_in1 = 0;
    expr_02_in2 = 1;
    expr_02_out1 = 0;
    expr_03_in1 = 0;
    expr_03_in2 = 100;
    expr_03_out1 = 0;
    expr_04_in1 = 0;
    expr_04_in2 = 2;
    expr_04_out1 = 0;
    param_05_value = 0.5;
    param_06_value = 1;
    param_07_value = 2;
    param_08_value = 0;
    param_09_value = 1;
    expr_05_in1 = 0;
    expr_05_in2 = 100;
    expr_05_out1 = 0;
    param_10_value = 1000;
    param_11_value = 80;
    param_12_value = 1;
    param_13_value = 1;
    param_14_value = 1;
    param_15_value = 1;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    signals[1] = nullptr;
    signals[2] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    numberobj_01_currentFormat = 6;
    numberobj_01_lastValue = 0;
    notein_01_status = 0;
    notein_01_byte1 = -1;
    notein_01_inchan = 0;
    gen_01_sampleCount_value = 0;
    gen_01_change_13_prev = 0;
    gen_01_change_14_prev = 0;
    gen_01_change_15_prev = 0;
    gen_01_change_16_prev = 0;
    gen_01_mtof_17_lastInValue = 0;
    gen_01_mtof_17_lastOutValue = 0;
    gen_01_mtof_17_lastTuning = 0;
    gen_01_phasor_18_currentPhase = 0;
    gen_01_phasor_18_conv = 0;
    gen_01_mtof_19_lastInValue = 0;
    gen_01_mtof_19_lastOutValue = 0;
    gen_01_mtof_19_lastTuning = 0;
    gen_01_mtof_22_lastInValue = 0;
    gen_01_mtof_22_lastOutValue = 0;
    gen_01_mtof_22_lastTuning = 0;
    gen_01_mtof_56_lastInValue = 0;
    gen_01_mtof_56_lastOutValue = 0;
    gen_01_mtof_56_lastTuning = 0;
    gen_01_mtof_75_lastInValue = 0;
    gen_01_mtof_75_lastOutValue = 0;
    gen_01_mtof_75_lastTuning = 0;
    gen_01_setupDone = false;
    rampsmooth_tilde_01_prev = 0;
    rampsmooth_tilde_01_index = 0;
    rampsmooth_tilde_01_increment = 0;
    rampsmooth_tilde_01_d_prev = 0;
    rampsmooth_tilde_01_setupDone = false;
    adsr_01_phase = 3;
    adsr_01_mspersamp = 0;
    adsr_01_time = 0;
    adsr_01_lastTriggerVal = 0;
    adsr_01_amplitude = 0;
    adsr_01_outval = 0;
    adsr_01_startingpoint = 0;
    adsr_01_triggerBuf = nullptr;
    adsr_01_triggerValueBuf = nullptr;
    adsr_01_setupDone = false;
    linetilde_01_currentValue = 1;
    param_01_lastValue = 0;
    param_02_lastValue = 0;
    param_03_lastValue = 0;
    param_04_lastValue = 0;
    param_05_lastValue = 0;
    param_06_lastValue = 0;
    param_07_lastValue = 0;
    param_08_lastValue = 0;
    param_09_lastValue = 0;
    param_10_lastValue = 0;
    param_11_lastValue = 0;
    param_12_lastValue = 0;
    param_13_lastValue = 0;
    param_14_lastValue = 0;
    param_15_lastValue = 0;
    globaltransport_tempo = nullptr;
    globaltransport_tempoNeedsReset = false;
    globaltransport_lastTempo = 120;
    globaltransport_state = nullptr;
    globaltransport_stateNeedsReset = false;
    globaltransport_lastState = 0;
    globaltransport_beatTimeChanges = { 0, 0 };
    globaltransport_timeSignatureChanges = { 4, 4, 0 };
    globaltransport_notify = false;
    globaltransport_setupDone = false;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

// member variables

    number numberobj_01_value;
    number dspexpr_01_in1;
    number dspexpr_01_in2;
    number dspexpr_02_in1;
    number dspexpr_02_in2;
    number notein_01_channel;
    number gen_01_in1;
    number gen_01_termsToAddPerCount;
    number gen_01_cycleCountToSubtract;
    number gen_01_cycleCountToAdd;
    number gen_01_PosNegSync;
    number gen_01_PosNeg;
    number gen_01_ocillator;
    number gen_01_attenuation;
    number gen_01_cutoffOvertone;
    number gen_01_filterOnOff;
    number gen_01_terms;
    number rampsmooth_tilde_01_x;
    number rampsmooth_tilde_01_up;
    number rampsmooth_tilde_01_down;
    number adsr_01_trigger_number;
    number adsr_01_attack;
    number adsr_01_decay;
    number adsr_01_sustain;
    number adsr_01_release;
    number adsr_01_legato;
    number expr_01_in1;
    number expr_01_in2;
    number expr_01_out1;
    list linetilde_01_segments;
    number linetilde_01_time;
    number linetilde_01_keepramp;
    number param_01_value;
    number param_02_value;
    number param_03_value;
    number param_04_value;
    number expr_02_in1;
    number expr_02_in2;
    number expr_02_out1;
    number expr_03_in1;
    number expr_03_in2;
    number expr_03_out1;
    number expr_04_in1;
    number expr_04_in2;
    number expr_04_out1;
    number param_05_value;
    number param_06_value;
    number param_07_value;
    number param_08_value;
    number param_09_value;
    number expr_05_in1;
    number expr_05_in2;
    number expr_05_out1;
    number param_10_value;
    number param_11_value;
    number param_12_value;
    number param_13_value;
    number param_14_value;
    number param_15_value;
    MillisecondTime _currentTime;
    SampleIndex audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[3];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    Int numberobj_01_currentFormat;
    number numberobj_01_lastValue;
    int notein_01_status;
    int notein_01_byte1;
    int notein_01_inchan;
    Float64BufferRef gen_01_manageParam;
    number gen_01_sampleCount_value;
    number gen_01_change_13_prev;
    number gen_01_change_14_prev;
    number gen_01_change_15_prev;
    number gen_01_change_16_prev;
    number gen_01_mtof_17_lastInValue;
    number gen_01_mtof_17_lastOutValue;
    number gen_01_mtof_17_lastTuning;
    Float64BufferRef gen_01_mtof_17_buffer;
    number gen_01_phasor_18_currentPhase;
    number gen_01_phasor_18_conv;
    number gen_01_mtof_19_lastInValue;
    number gen_01_mtof_19_lastOutValue;
    number gen_01_mtof_19_lastTuning;
    Float64BufferRef gen_01_mtof_19_buffer;
    number gen_01_mtof_22_lastInValue;
    number gen_01_mtof_22_lastOutValue;
    number gen_01_mtof_22_lastTuning;
    Float64BufferRef gen_01_mtof_22_buffer;
    number gen_01_mtof_56_lastInValue;
    number gen_01_mtof_56_lastOutValue;
    number gen_01_mtof_56_lastTuning;
    Float64BufferRef gen_01_mtof_56_buffer;
    number gen_01_mtof_75_lastInValue;
    number gen_01_mtof_75_lastOutValue;
    number gen_01_mtof_75_lastTuning;
    Float64BufferRef gen_01_mtof_75_buffer;
    bool gen_01_setupDone;
    number rampsmooth_tilde_01_prev;
    number rampsmooth_tilde_01_index;
    number rampsmooth_tilde_01_increment;
    number rampsmooth_tilde_01_d_prev;
    bool rampsmooth_tilde_01_setupDone;
    Int adsr_01_phase;
    number adsr_01_mspersamp;
    number adsr_01_time;
    number adsr_01_lastTriggerVal;
    number adsr_01_amplitude;
    number adsr_01_outval;
    number adsr_01_startingpoint;
    signal adsr_01_triggerBuf;
    signal adsr_01_triggerValueBuf;
    bool adsr_01_setupDone;
    list linetilde_01_activeRamps;
    number linetilde_01_currentValue;
    number param_01_lastValue;
    number param_02_lastValue;
    number param_03_lastValue;
    number param_04_lastValue;
    number param_05_lastValue;
    number param_06_lastValue;
    number param_07_lastValue;
    number param_08_lastValue;
    number param_09_lastValue;
    number param_10_lastValue;
    number param_11_lastValue;
    number param_12_lastValue;
    number param_13_lastValue;
    number param_14_lastValue;
    number param_15_lastValue;
    signal globaltransport_tempo;
    bool globaltransport_tempoNeedsReset;
    number globaltransport_lastTempo;
    signal globaltransport_state;
    bool globaltransport_stateNeedsReset;
    number globaltransport_lastState;
    list globaltransport_beatTimeChanges;
    list globaltransport_timeSignatureChanges;
    bool globaltransport_notify;
    bool globaltransport_setupDone;
    number stackprotect_count;
    DataRef manageParam;
    DataRef RNBODefaultMtofLookupTable256;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;

};

PatcherInterface* creaternbomatic()
{
    return new rnbomatic();
}

#ifndef RNBO_NO_PATCHERFACTORY

extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction(PlatformInterface* platformInterface)
#else

extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction(PlatformInterface* platformInterface)
#endif

{
    Platform::set(platformInterface);
    return creaternbomatic;
}

} // end RNBO namespace

