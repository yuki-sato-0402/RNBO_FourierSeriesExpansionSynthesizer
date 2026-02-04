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

#ifdef RNBO_LIB_PREFIX
#define STR_IMPL(A) #A
#define STR(A) STR_IMPL(A)
#define RNBO_LIB_INCLUDE(X) STR(RNBO_LIB_PREFIX/X)
#else
#define RNBO_LIB_INCLUDE(X) #X
#endif // RNBO_LIB_PREFIX
#ifdef RNBO_INJECTPLATFORM
#define RNBO_USECUSTOMPLATFORM
#include RNBO_INJECTPLATFORM
#endif // RNBO_INJECTPLATFORM

#include RNBO_LIB_INCLUDE(RNBO_Common.h)
#include RNBO_LIB_INCLUDE(RNBO_AudioSignal.h)

namespace RNBO {


#define trunc(x) ((Int)(x))
#define autoref auto&

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

template <class ENGINE = INTERNALENGINE> class rnbomatic : public PatcherInterfaceImpl {

friend class EngineCore;
friend class Engine;
friend class MinimalEngine<>;
public:

rnbomatic()
: _internalEngine(this)
{
}

~rnbomatic()
{
    deallocateSignals();
}

Index getNumMidiInputPorts() const {
    return 1;
}

void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
    this->updateTime(time, (ENGINE*)nullptr);
    this->notein_01_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_01_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_02_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_03_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_04_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_05_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_06_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_07_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_08_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_09_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_10_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_11_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_12_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_13_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_14_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_15_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_16_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_17_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
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
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr, true);
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    SampleValue * out3 = (numOutputs >= 3 && outputs[2] ? outputs[2] : this->dummyBuffer);

    this->gen_01_perform(
        this->gen_01_in1,
        this->gen_01_terms,
        this->gen_01_filterOnOff,
        this->gen_01_cutoffOvertone,
        this->gen_01_attenuation,
        this->gen_01_ocillator,
        this->gen_01_PosNeg,
        this->gen_01_PosNegSync,
        this->gen_01_cycleCountToAdd,
        this->gen_01_cycleCountToSubtract,
        this->gen_01_termsToAddPerCount,
        this->gen_01_harmonicSeriesMode,
        this->gen_01_harmonicRatio,
        this->signals[0],
        out3,
        n
    );

    this->delaytilde_01_perform(this->delaytilde_01_delay, this->signals[0], this->signals[1], n);

    this->adsr_01_perform(
        this->adsr_01_attack,
        this->adsr_01_decay,
        this->adsr_01_sustain,
        this->adsr_01_release,
        this->zeroBuffer,
        this->signals[0],
        n
    );

    this->delaytilde_02_perform(this->delaytilde_02_delay, this->signals[0], this->signals[2], n);
    this->linetilde_01_perform(this->signals[0], n);
    this->linetilde_02_perform(this->signals[3], n);
    this->dspexpr_03_perform(this->signals[2], this->signals[3], this->signals[4], n);
    this->dspexpr_02_perform(this->signals[1], this->signals[4], this->signals[3], n);
    this->dspexpr_01_perform(this->signals[3], this->signals[0], this->signals[4], n);
    this->signalforwarder_01_perform(this->signals[4], out2, n);
    this->signalforwarder_02_perform(this->signals[4], out1, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->advanceTime((ENGINE*)nullptr);
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    RNBO_ASSERT(this->_isInitialized);

    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 5; i++) {
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

    this->delaytilde_01_dspsetup(forceDSPSetup);
    this->adsr_01_dspsetup(forceDSPSetup);
    this->delaytilde_02_dspsetup(forceDSPSetup);
    this->globaltransport_dspsetup(forceDSPSetup);

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getNumInputChannels() const {
    return 0;
}

Index getNumOutputChannels() const {
    return 3;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    case 0:
        {
        return addressOf(this->delaytilde_01_del_bufferobj);
        break;
        }
    case 1:
        {
        return addressOf(this->phaseStore);
        break;
        }
    case 2:
        {
        return addressOf(this->manageParam);
        break;
        }
    case 3:
        {
        return addressOf(this->RNBODefaultMtofLookupTable256);
        break;
        }
    case 4:
        {
        return addressOf(this->delaytilde_02_del_bufferobj);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 5;
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (index == 0) {
        this->delaytilde_01_del_buffer = reInitDataView(this->delaytilde_01_del_buffer, this->delaytilde_01_del_bufferobj);
    }

    if (index == 1) {
        this->gen_01_phaseStore = reInitDataView(this->gen_01_phaseStore, this->phaseStore);
    }

    if (index == 2) {
        this->gen_01_manageParam = reInitDataView(this->gen_01_manageParam, this->manageParam);
    }

    if (index == 3) {
        this->gen_01_mtof_11_buffer = reInitDataView(this->gen_01_mtof_11_buffer, this->RNBODefaultMtofLookupTable256);
        this->gen_01_mtof_78_buffer = reInitDataView(this->gen_01_mtof_78_buffer, this->RNBODefaultMtofLookupTable256);
        this->gen_01_mtof_79_buffer = reInitDataView(this->gen_01_mtof_79_buffer, this->RNBODefaultMtofLookupTable256);
    }

    if (index == 4) {
        this->delaytilde_02_del_buffer = reInitDataView(this->delaytilde_02_del_buffer, this->delaytilde_02_del_bufferobj);
    }
}

void initialize() {
    RNBO_ASSERT(!this->_isInitialized);

    this->delaytilde_01_del_bufferobj = initDataRef(
        this->delaytilde_01_del_bufferobj,
        this->dataRefStrings->name0,
        true,
        this->dataRefStrings->file0,
        this->dataRefStrings->tag0
    );

    this->phaseStore = initDataRef(
        this->phaseStore,
        this->dataRefStrings->name1,
        true,
        this->dataRefStrings->file1,
        this->dataRefStrings->tag1
    );

    this->manageParam = initDataRef(
        this->manageParam,
        this->dataRefStrings->name2,
        true,
        this->dataRefStrings->file2,
        this->dataRefStrings->tag2
    );

    this->RNBODefaultMtofLookupTable256 = initDataRef(
        this->RNBODefaultMtofLookupTable256,
        this->dataRefStrings->name3,
        true,
        this->dataRefStrings->file3,
        this->dataRefStrings->tag3
    );

    this->delaytilde_02_del_bufferobj = initDataRef(
        this->delaytilde_02_del_bufferobj,
        this->dataRefStrings->name4,
        true,
        this->dataRefStrings->file4,
        this->dataRefStrings->tag4
    );

    this->assign_defaults();
    this->applyState();
    this->delaytilde_01_del_bufferobj->setIndex(0);
    this->delaytilde_01_del_buffer = new Float64Buffer(this->delaytilde_01_del_bufferobj);
    this->phaseStore->setIndex(1);
    this->gen_01_phaseStore = new SampleBuffer(this->phaseStore);
    this->manageParam->setIndex(2);
    this->gen_01_manageParam = new SampleBuffer(this->manageParam);
    this->RNBODefaultMtofLookupTable256->setIndex(3);
    this->gen_01_mtof_11_buffer = new SampleBuffer(this->RNBODefaultMtofLookupTable256);
    this->gen_01_mtof_78_buffer = new SampleBuffer(this->RNBODefaultMtofLookupTable256);
    this->gen_01_mtof_79_buffer = new SampleBuffer(this->RNBODefaultMtofLookupTable256);
    this->delaytilde_02_del_bufferobj->setIndex(4);
    this->delaytilde_02_del_buffer = new Float64Buffer(this->delaytilde_02_del_bufferobj);
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
    this->_isInitialized = true;
}

void getPreset(PatcherStateInterface& preset) {
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
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
    this->param_12_getPresetValue(getSubState(preset, "harmonicRatio"));
    this->param_13_getPresetValue(getSubState(preset, "harmonicSeriesMode"));
    this->param_14_getPresetValue(getSubState(preset, "PosNegSync"));
    this->param_15_getPresetValue(getSubState(preset, "termsToAddPerCount"));
    this->param_16_getPresetValue(getSubState(preset, "cycleCountToSubtract"));
    this->param_17_getPresetValue(getSubState(preset, "cycleCountToAdd"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time, (ENGINE*)nullptr);
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
    this->param_12_setPresetValue(getSubState(preset, "harmonicRatio"));
    this->param_13_setPresetValue(getSubState(preset, "harmonicSeriesMode"));
    this->param_14_setPresetValue(getSubState(preset, "PosNegSync"));
    this->param_15_setPresetValue(getSubState(preset, "termsToAddPerCount"));
    this->param_16_setPresetValue(getSubState(preset, "cycleCountToSubtract"));
    this->param_17_setPresetValue(getSubState(preset, "cycleCountToAdd"));
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time, (ENGINE*)nullptr);

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
    case 15:
        {
        this->param_16_value_set(v);
        break;
        }
    case 16:
        {
        this->param_17_value_set(v);
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
    case 15:
        {
        return this->param_16_value;
        }
    case 16:
        {
        return this->param_17_value;
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
    return 17;
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
        return "harmonicRatio";
        }
    case 12:
        {
        return "harmonicSeriesMode";
        }
    case 13:
        {
        return "PosNegSync";
        }
    case 14:
        {
        return "termsToAddPerCount";
        }
    case 15:
        {
        return "cycleCountToSubtract";
        }
    case 16:
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
        return "harmonicRatio";
        }
    case 12:
        {
        return "harmonicSeriesMode";
        }
    case 13:
        {
        return "PosNegSync";
        }
    case 14:
        {
        return "termsToAddPerCount";
        }
    case 15:
        {
        return "cycleCountToSubtract";
        }
    case 16:
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
            info->min = 0.1;
            info->max = 2;
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
        case 13:
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
        case 14:
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
        case 15:
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
        case 16:
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
    case 12:
    case 13:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);
            return normalizedValue;
        }
        }
    case 15:
    case 16:
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
    case 14:
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
    case 11:
        {
        {
            value = (value < 0.1 ? 0.1 : (value > 2 ? 2 : value));
            ParameterValue normalizedValue = (value - 0.1) / (2 - 0.1);
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
    case 12:
    case 13:
        {
        {
            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 15:
    case 16:
        {
        {
            {
                return 0 + value * (20 - 0);
            }
        }
        }
    case 10:
        {
        {
            {
                return 0 + value * (100 - 0);
            }
        }
        }
    case 9:
        {
        {
            {
                return 0 + value * (5000 - 0);
            }
        }
        }
    case 3:
        {
        {
            {
                return 1 + value * (3 - 1);
            }
        }
        }
    case 14:
        {
        {
            {
                return 1 + value * (20 - 1);
            }
        }
        }
    case 8:
        {
        {
            {
                return 1 + value * (40 - 1);
            }
        }
        }
    case 5:
        {
        {
            {
                return 1 + value * (100 - 1);
            }
        }
        }
    case 1:
    case 2:
        {
        {
            {
                return 1 + value * (1000 - 1);
            }
        }
        }
    case 6:
        {
        {
            {
                return 2 + value * (40 - 2);
            }
        }
        }
    case 11:
        {
        {
            {
                return 0.1 + value * (2 - 0.1);
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
    case 15:
        {
        return this->param_16_value_constrain(value);
        }
    case 16:
        {
        return this->param_17_value_constrain(value);
        }
    default:
        {
        return value;
        }
    }
}

void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
    this->updateTime(time, (ENGINE*)nullptr);

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
    case TAG("listin"):
        {
        if (TAG("message_obj-46") == objectId)
            this->message_01_listin_number_set(payload);

        break;
        }
    }
}

void processListMessage(
    MessageTag tag,
    MessageTag objectId,
    MillisecondTime time,
    const list& payload
) {
    this->updateTime(time, (ENGINE*)nullptr);

    switch (tag) {
    case TAG("listin"):
        {
        if (TAG("message_obj-46") == objectId)
            this->message_01_listin_list_set(payload);

        break;
        }
    }
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    this->updateTime(time, (ENGINE*)nullptr);

    switch (tag) {
    case TAG("listin"):
        {
        if (TAG("message_obj-46") == objectId)
            this->message_01_listin_bang_bang();

        break;
        }
    case TAG("startupbang"):
        {
        if (TAG("loadmess_obj-84") == objectId)
            this->loadmess_01_startupbang_bang();

        break;
        }
    }
}

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
    case TAG("listout"):
        {
        return "listout";
        }
    case TAG("message_obj-46"):
        {
        return "message_obj-46";
        }
    case TAG("valin"):
        {
        return "valin";
        }
    case TAG("format"):
        {
        return "format";
        }
    case TAG("listin"):
        {
        return "listin";
        }
    case TAG("startupbang"):
        {
        return "startupbang";
        }
    case TAG("loadmess_obj-84"):
        {
        return "loadmess_obj-84";
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

		
void advanceTime(EXTERNALENGINE*) {}
void advanceTime(INTERNALENGINE*) {
	_internalEngine.advanceTime(sampstoms(this->vs));
}

void processInternalEvents(MillisecondTime time) {
	_internalEngine.processEventsUntil(time);
}

void updateTime(MillisecondTime time, INTERNALENGINE*, bool inProcess = false) {
	if (time == TimeNow) time = getPatcherTime();
	processInternalEvents(inProcess ? time + sampsToMs(this->vs) : time);
	updateTime(time, (EXTERNALENGINE*)nullptr);
}

rnbomatic* operator->() {
    return this;
}
const rnbomatic* operator->() const {
    return this;
}
rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
    getEngine()->flushClockEvents(this, 892732297, false);
    getEngine()->flushClockEvents(this, -1468824490, false);
    getEngine()->flushClockEvents(this, -62043057, false);
    getEngine()->flushClockEvents(this, -281953904, false);
}

template<typename LISTTYPE = list> void listquicksort(LISTTYPE& arr, LISTTYPE& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template<typename LISTTYPE = list> Int listpartition(LISTTYPE& arr, LISTTYPE& sortindices, Int l, Int h, bool ascending) {
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

template<typename LISTTYPE = list> void listswapelements(LISTTYPE& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

inline number linearinterp(number frac, number x, number y) {
    return x + (y - x) * frac;
}

inline number cubicinterp(number a, number w, number x, number y, number z) {
    number a1 = 1. + a;
    number aa = a * a1;
    number b = 1. - a;
    number b1 = 2. - a;
    number bb = b * b1;
    number fw = -.1666667 * bb * a;
    number fx = .5 * bb * a1;
    number fy = .5 * aa * b1;
    number fz = -.1666667 * aa * b;
    return w * fw + x * fx + y * fy + z * fz;
}

inline number fastcubicinterp(number a, number w, number x, number y, number z) {
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

inline number spline6interp(number a, number y0, number y1, number y2, number y3, number y4, number y5) {
    number ym2py2 = y0 + y4;
    number ym1py1 = y1 + y3;
    number y2mym2 = y4 - y0;
    number y1mym1 = y3 - y1;
    number sixthym1py1 = (number)1 / (number)6.0 * ym1py1;
    number c0 = (number)1 / (number)120.0 * ym2py2 + (number)13 / (number)60.0 * ym1py1 + (number)11 / (number)20.0 * y2;
    number c1 = (number)1 / (number)24.0 * y2mym2 + (number)5 / (number)12.0 * y1mym1;
    number c2 = (number)1 / (number)12.0 * ym2py2 + sixthym1py1 - (number)1 / (number)2.0 * y2;
    number c3 = (number)1 / (number)12.0 * y2mym2 - (number)1 / (number)6.0 * y1mym1;
    number c4 = (number)1 / (number)24.0 * ym2py2 - sixthym1py1 + (number)1 / (number)4.0 * y2;
    number c5 = (number)1 / (number)120.0 * (y5 - y0) + (number)1 / (number)24.0 * (y1 - y4) + (number)1 / (number)12.0 * (y3 - y2);
    return ((((c5 * a + c4) * a + c3) * a + c2) * a + c1) * a + c0;
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

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

number maximum(number x, number y) {
    return (x < y ? y : x);
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

    Int numWraps = (Int)(trunc((x - lo) / range));
    numWraps = numWraps - ((x < lo ? 1 : 0));
    number result = x - range * numWraps;

    if (result >= hi)
        return result - range;
    else
        return result;
}

template<typename BUFFERTYPE> void poke_default(
    BUFFERTYPE& buffer,
    SampleValue value,
    SampleValue sampleIndex,
    Int channel,
    number overdub
) {
    number bufferSize = buffer->getSize();
    const Index bufferChannels = (const Index)(buffer->getChannels());

    if (bufferSize > 0 && (5 != 5 || (sampleIndex >= 0 && sampleIndex < bufferSize)) && (5 != 5 || (channel >= 0 && channel < bufferChannels))) {
        if (overdub != 0) {
            number currentValue = buffer->getSample(channel, sampleIndex);

            {
                value = value + currentValue * overdub;
            }
        }

        buffer->setSample(channel, sampleIndex, value);
        buffer->setTouched(true);
    }
}

template<typename BUFFERTYPE> array<SampleValue, 1 + 1> peek_default(BUFFERTYPE& buffer, SampleValue sampleIndex, Index channelOffset) {
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

                SampleIndex truncIndex = (SampleIndex)(trunc(sampleIndex));

                {
                    bufferreadsample_result = __buffer->getSample(channelIndex, truncIndex);
                }
            }

            out[(Index)channel] = bufferreadsample_result;
        }

        out[1] = sampleIndex;
        return out;
    }
}

inline number intnum(const number value) {
    return trunc(value);
}

UInt64 currentsampletime() {
    return this->audioProcessSampleCount + this->sampleOffsetIntoNextAudioBuffer;
}

number fromnormalized(Index index, number normalizedValue) {
    return this->convertFromNormalizedParameterValue(index, normalizedValue);
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

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
        listbase<number, 1> converted = {v};
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

    this->expr_08_in1_set(v);
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

    this->expr_14_in1_set(v);
}

void param_12_value_set(number v) {
    v = this->param_12_value_constrain(v);
    this->param_12_value = v;
    this->sendParameter(11, false);

    if (this->param_12_value != this->param_12_lastValue) {
        this->getEngine()->presetTouched();
        this->param_12_lastValue = this->param_12_value;
    }

    this->gen_01_harmonicRatio_set(v);
}

void param_13_value_set(number v) {
    v = this->param_13_value_constrain(v);
    this->param_13_value = v;
    this->sendParameter(12, false);

    if (this->param_13_value != this->param_13_lastValue) {
        this->getEngine()->presetTouched();
        this->param_13_lastValue = this->param_13_value;
    }

    this->gen_01_harmonicSeriesMode_set(v);
}

void param_14_value_set(number v) {
    v = this->param_14_value_constrain(v);
    this->param_14_value = v;
    this->sendParameter(13, false);

    if (this->param_14_value != this->param_14_lastValue) {
        this->getEngine()->presetTouched();
        this->param_14_lastValue = this->param_14_value;
    }

    this->gen_01_PosNegSync_set(v);
}

void param_15_value_set(number v) {
    v = this->param_15_value_constrain(v);
    this->param_15_value = v;
    this->sendParameter(14, false);

    if (this->param_15_value != this->param_15_lastValue) {
        this->getEngine()->presetTouched();
        this->param_15_lastValue = this->param_15_value;
    }

    this->gen_01_termsToAddPerCount_set(v);
}

void param_16_value_set(number v) {
    v = this->param_16_value_constrain(v);
    this->param_16_value = v;
    this->sendParameter(15, false);

    if (this->param_16_value != this->param_16_lastValue) {
        this->getEngine()->presetTouched();
        this->param_16_lastValue = this->param_16_value;
    }

    this->gen_01_cycleCountToSubtract_set(v);
}

void param_17_value_set(number v) {
    v = this->param_17_value_constrain(v);
    this->param_17_value = v;
    this->sendParameter(16, false);

    if (this->param_17_value != this->param_17_lastValue) {
        this->getEngine()->presetTouched();
        this->param_17_lastValue = this->param_17_value;
    }

    this->gen_01_cycleCountToAdd_set(v);
}

MillisecondTime getPatcherTime() const {
    return this->_currentTime;
}

void numberobj_01_valin_set(number v) {
    this->numberobj_01_value_set(v);
}

void numberobj_01_format_set(number v) {
    this->numberobj_01_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

template<typename LISTTYPE> void message_01_listin_list_set(const LISTTYPE& v) {
    this->message_01_set_set(v);
}

void message_01_listin_number_set(number v) {
    this->message_01_set_set(v);
}

void message_01_listin_bang_bang() {
    this->message_01_trigger_bang();
}

void loadmess_01_startupbang_bang() {
    this->loadmess_01_message_bang();
}

void adsr_01_mute_bang() {}

void linetilde_01_target_bang() {}

void linetilde_02_target_bang() {}

void deallocateSignals() {
    Index i;

    for (i = 0; i < 5; i++) {
        this->signals[i] = freeSignal(this->signals[i]);
    }

    this->adsr_01_triggerBuf = freeSignal(this->adsr_01_triggerBuf);
    this->adsr_01_triggerValueBuf = freeSignal(this->adsr_01_triggerValueBuf);
    this->globaltransport_tempo = freeSignal(this->globaltransport_tempo);
    this->globaltransport_state = freeSignal(this->globaltransport_state);
    this->zeroBuffer = freeSignal(this->zeroBuffer);
    this->dummyBuffer = freeSignal(this->dummyBuffer);
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

void setProbingTarget(MessageTag ) {}

void fillRNBODefaultMtofLookupTable256(DataRef& ref) {
    SampleBuffer buffer(ref);
    number bufsize = buffer->getSize();

    for (Index i = 0; i < bufsize; i++) {
        number midivalue = -256. + (number)512. / (bufsize - 1) * i;
        buffer[i] = rnbo_exp(.057762265 * (midivalue - 69.0));
    }
}

void fillDataRef(DataRefIndex index, DataRef& ref) {
    switch (index) {
    case 3:
        {
        this->fillRNBODefaultMtofLookupTable256(ref);
        break;
        }
    }
}

void zeroDataRef(DataRef& ref) {
    ref->setZero();
}

void allocateDataRefs() {
    this->gen_01_phaseStore->requestSize(40, 2);
    this->gen_01_phaseStore->setSampleRate(this->sr);
    this->gen_01_manageParam->requestSize(10, 1);
    this->gen_01_manageParam->setSampleRate(this->sr);
    this->gen_01_mtof_11_buffer->requestSize(65536, 1);
    this->gen_01_mtof_11_buffer->setSampleRate(this->sr);
    this->gen_01_mtof_78_buffer->requestSize(65536, 1);
    this->gen_01_mtof_78_buffer->setSampleRate(this->sr);
    this->gen_01_mtof_79_buffer->requestSize(65536, 1);
    this->gen_01_mtof_79_buffer->setSampleRate(this->sr);
    this->delaytilde_01_del_buffer = this->delaytilde_01_del_buffer->allocateIfNeeded();

    if (this->delaytilde_01_del_bufferobj->hasRequestedSize()) {
        if (this->delaytilde_01_del_bufferobj->wantsFill())
            this->zeroDataRef(this->delaytilde_01_del_bufferobj);

        this->getEngine()->sendDataRefUpdated(0);
    }

    this->gen_01_phaseStore = this->gen_01_phaseStore->allocateIfNeeded();

    if (this->phaseStore->hasRequestedSize()) {
        if (this->phaseStore->wantsFill())
            this->zeroDataRef(this->phaseStore);

        this->getEngine()->sendDataRefUpdated(1);
    }

    this->gen_01_manageParam = this->gen_01_manageParam->allocateIfNeeded();

    if (this->manageParam->hasRequestedSize()) {
        if (this->manageParam->wantsFill())
            this->zeroDataRef(this->manageParam);

        this->getEngine()->sendDataRefUpdated(2);
    }

    this->gen_01_mtof_11_buffer = this->gen_01_mtof_11_buffer->allocateIfNeeded();
    this->gen_01_mtof_78_buffer = this->gen_01_mtof_78_buffer->allocateIfNeeded();
    this->gen_01_mtof_79_buffer = this->gen_01_mtof_79_buffer->allocateIfNeeded();

    if (this->RNBODefaultMtofLookupTable256->hasRequestedSize()) {
        if (this->RNBODefaultMtofLookupTable256->wantsFill())
            this->fillRNBODefaultMtofLookupTable256(this->RNBODefaultMtofLookupTable256);

        this->getEngine()->sendDataRefUpdated(3);
    }

    this->delaytilde_02_del_buffer = this->delaytilde_02_del_buffer->allocateIfNeeded();

    if (this->delaytilde_02_del_bufferobj->hasRequestedSize()) {
        if (this->delaytilde_02_del_bufferobj->wantsFill())
            this->zeroDataRef(this->delaytilde_02_del_bufferobj);

        this->getEngine()->sendDataRefUpdated(4);
    }
}

void initializeObjects() {
    this->delaytilde_01_del_init();
    this->numberobj_01_init();
    this->gen_01_sampleCount_init();
    this->gen_01_change_8_init();
    this->gen_01_change_9_init();
    this->gen_01_change_10_init();
    this->gen_01_change_70_init();
    this->gen_01_change_71_init();
    this->gen_01_change_72_init();
    this->gen_01_change_73_init();
    this->gen_01_change_74_init();
    this->gen_01_change_75_init();
    this->gen_01_change_76_init();
    this->gen_01_change_77_init();
    this->delaytilde_02_del_init();
    this->change_01_init();
    this->message_01_init();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

void onSampleRateChanged(double ) {}

void extractState(PatcherStateInterface& ) {}

void applyState() {}

void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
    RNBO_UNUSED(value);
    RNBO_UNUSED(hasValue);
    this->updateTime(time, (ENGINE*)nullptr);

    switch (index) {
    case 892732297:
        {
        this->loadmess_01_startupbang_bang();
        break;
        }
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
    case -281953904:
        {
        this->linetilde_02_target_bang();
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
    this->updateTime(time, (ENGINE*)nullptr);
    this->processOutletAtCurrentTime(sender, index, value);
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
    this->getEngine()->scheduleClockEvent(this, 892732297, 0 + this->_currentTime);;

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

    {
        this->scheduleParamInit(15, 0);
    }

    {
        this->scheduleParamInit(16, 0);
    }

    this->processParamInitEvents();
}

number param_01_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void gen_01_PosNeg_set(number v) {
    this->gen_01_PosNeg = v;
}

number param_02_value_constrain(number v) const {
    v = (v > 1000 ? 1000 : (v < 1 ? 1 : v));
    return v;
}

void adsr_01_decay_set(number v) {
    this->adsr_01_decay = v;
}

number param_03_value_constrain(number v) const {
    v = (v > 1000 ? 1000 : (v < 1 ? 1 : v));
    return v;
}

void adsr_01_attack_set(number v) {
    this->adsr_01_attack = v;
}

number param_04_value_constrain(number v) const {
    v = (v > 3 ? 3 : (v < 1 ? 1 : v));
    return v;
}

void gen_01_ocillator_set(number v) {
    this->gen_01_ocillator = v;
}

number param_05_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void linetilde_01_time_set(number v) {
    this->linetilde_01_time = v;
}

template<typename LISTTYPE> void linetilde_01_segments_set(const LISTTYPE& v) {
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

number param_06_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < 1 ? 1 : v));
    return v;
}

void gen_01_attenuation_set(number v) {
    this->gen_01_attenuation = v;
}

void expr_06_out1_set(number v) {
    this->expr_06_out1 = v;
    this->gen_01_attenuation_set(this->expr_06_out1);
}

void expr_06_in1_set(number in1) {
    this->expr_06_in1 = in1;
    this->expr_06_out1_set(this->expr_06_in1 + this->expr_06_in2);//#map:+_obj-37:1
}

void expr_07_out1_set(number v) {
    this->expr_07_out1 = v;
    this->expr_06_in1_set(this->expr_07_out1);
}

void expr_07_in1_set(number in1) {
    this->expr_07_in1 = in1;

    this->expr_07_out1_set(
        (this->expr_07_in2 == 0 ? 0 : (this->expr_07_in2 == 0. ? 0. : this->expr_07_in1 / this->expr_07_in2))
    );//#map:/_obj-36:1
}

void expr_08_out1_set(number v) {
    this->expr_08_out1 = v;
    this->expr_07_in1_set(this->expr_08_out1);
}

void expr_08_in1_set(number in1) {
    this->expr_08_in1 = in1;
    this->expr_08_out1_set(fixnan(rnbo_pow(this->expr_08_in1, this->expr_08_in2)));//#map:pow_obj-31:1
}

number param_07_value_constrain(number v) const {
    v = (v > 40 ? 40 : (v < 2 ? 2 : v));
    return v;
}

void gen_01_cutoffOvertone_set(number v) {
    this->gen_01_cutoffOvertone = v;
}

number param_08_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void gen_01_filterOnOff_set(number v) {
    this->gen_01_filterOnOff = v;
}

number param_09_value_constrain(number v) const {
    v = (v > 40 ? 40 : (v < 1 ? 1 : v));
    return v;
}

void gen_01_terms_set(number v) {
    this->gen_01_terms = v;
}

number param_10_value_constrain(number v) const {
    v = (v > 5000 ? 5000 : (v < 0 ? 0 : v));
    return v;
}

void adsr_01_release_set(number v) {
    this->adsr_01_release = v;
}

number param_11_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

void adsr_01_sustain_set(number v) {
    this->adsr_01_sustain = v;
}

void expr_14_out1_set(number v) {
    this->expr_14_out1 = v;
    this->adsr_01_sustain_set(this->expr_14_out1);
}

void expr_14_in1_set(number in1) {
    this->expr_14_in1 = in1;

    this->expr_14_out1_set(
        (this->expr_14_in2 == 0 ? 0 : (this->expr_14_in2 == 0. ? 0. : this->expr_14_in1 / this->expr_14_in2))
    );//#map:/_obj-43:1
}

number param_12_value_constrain(number v) const {
    v = (v > 2 ? 2 : (v < 0.1 ? 0.1 : v));
    return v;
}

void gen_01_harmonicRatio_set(number v) {
    this->gen_01_harmonicRatio = v;
}

number param_13_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void gen_01_harmonicSeriesMode_set(number v) {
    this->gen_01_harmonicSeriesMode = v;
}

number param_14_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void gen_01_PosNegSync_set(number v) {
    this->gen_01_PosNegSync = v;
}

number param_15_value_constrain(number v) const {
    v = (v > 20 ? 20 : (v < 1 ? 1 : v));
    return v;
}

void gen_01_termsToAddPerCount_set(number v) {
    this->gen_01_termsToAddPerCount = v;
}

number param_16_value_constrain(number v) const {
    v = (v > 20 ? 20 : (v < 0 ? 0 : v));
    return v;
}

void gen_01_cycleCountToSubtract_set(number v) {
    this->gen_01_cycleCountToSubtract = v;
}

number param_17_value_constrain(number v) const {
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

    this->numberobj_01_output_set(localvalue);
}

template<typename LISTTYPE> void message_01_set_set(const LISTTYPE& v) {
    this->message_01_set = jsCreateListCopy(v);
}

void linetilde_02_time_set(number v) {
    this->linetilde_02_time = v;
}

template<typename LISTTYPE> void linetilde_02_segments_set(const LISTTYPE& v) {
    this->linetilde_02_segments = jsCreateListCopy(v);

    if ((bool)(v->length)) {
        if (v->length == 1 && this->linetilde_02_time == 0) {
            this->linetilde_02_activeRamps->length = 0;
            this->linetilde_02_currentValue = v[0];
        } else {
            auto currentTime = this->currentsampletime();
            number lastRampValue = this->linetilde_02_currentValue;
            number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;

            for (Index i = 0; i < this->linetilde_02_activeRamps->length; i += 3) {
                rampEnd = this->linetilde_02_activeRamps[(Index)(i + 2)];

                if (rampEnd > currentTime) {
                    this->linetilde_02_activeRamps[(Index)(i + 2)] = currentTime;
                    number diff = rampEnd - currentTime;
                    number valueDiff = diff * this->linetilde_02_activeRamps[(Index)(i + 1)];
                    lastRampValue = this->linetilde_02_activeRamps[(Index)i] - valueDiff;
                    this->linetilde_02_activeRamps[(Index)i] = lastRampValue;
                    this->linetilde_02_activeRamps->length = i + 3;
                    rampEnd = currentTime;
                } else {
                    lastRampValue = this->linetilde_02_activeRamps[(Index)i];
                }
            }

            if (rampEnd < currentTime) {
                this->linetilde_02_activeRamps->push(lastRampValue);
                this->linetilde_02_activeRamps->push(0);
                this->linetilde_02_activeRamps->push(currentTime);
            }

            number lastRampEnd = currentTime;

            for (Index i = 0; i < v->length; i += 2) {
                number destinationValue = v[(Index)i];
                number inc = 0;
                number rampTimeInSamples;

                if (v->length > i + 1) {
                    rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);

                    if ((bool)(this->linetilde_02_keepramp)) {
                        this->linetilde_02_time_set(v[(Index)(i + 1)]);
                    }
                } else {
                    rampTimeInSamples = this->mstosamps(this->linetilde_02_time);
                }

                if (rampTimeInSamples <= 0) {
                    rampTimeInSamples = 1;
                }

                inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                lastRampEnd += rampTimeInSamples;
                this->linetilde_02_activeRamps->push(destinationValue);
                this->linetilde_02_activeRamps->push(inc);
                this->linetilde_02_activeRamps->push(lastRampEnd);
                lastRampValue = destinationValue;
            }
        }
    }
}

template<typename LISTTYPE> void message_01_out_set(const LISTTYPE& v) {
    this->linetilde_02_segments_set(v);
}

void message_01_trigger_bang() {
    if ((bool)(this->message_01_set->length) || (bool)(false)) {
        this->message_01_out_set(this->message_01_set);
    }
}

void delaytilde_01_delay_set(number v) {
    this->delaytilde_01_delay = v;
}

void delaytilde_02_delay_set(number v) {
    this->delaytilde_02_delay = v;
}

void mstosamps_01_out1_set(number v) {
    this->delaytilde_01_delay_set(v);
    this->delaytilde_02_delay_set(v);
}

void mstosamps_01_ms_set(number ms) {
    this->mstosamps_01_ms = ms;

    {
        this->mstosamps_01_out1_set(ms * this->sr * 0.001);
        return;
    }
}

void loadmess_01_message_bang() {
    list v = this->loadmess_01_message;

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->mstosamps_01_ms_set(converted);
    }
}

void notein_01_outchannel_set(number ) {}

void notein_01_releasevelocity_set(number ) {}

void change_01_zero_set(number ) {}

void change_01_nonzero_set(number v) {
    RNBO_UNUSED(v);
    this->message_01_trigger_bang();
}

void change_01_out_set(number v) {
    this->change_01_out = v;
}

void change_01_input_set(number v) {
    this->change_01_input = v;

    if (v != this->change_01_prev) {
        if (v == 0) {
            this->change_01_zero_set(1);
        } else if (this->change_01_out == 0) {
            this->change_01_nonzero_set(1);
        }

        {
            this->change_01_out_set(v);
        }
    }

    this->change_01_prev = v;
}

void adsr_01_trigger_number_set(number v) {
    this->adsr_01_trigger_number = v;

    if (v != 0)
        this->adsr_01_triggerBuf[this->sampleOffsetIntoNextAudioBuffer] = 1;

    for (number i = this->sampleOffsetIntoNextAudioBuffer; i < this->vs; i++) {
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
    this->change_01_input_set(v);
    this->expr_01_in1_set(v);
}

void notein_01_notenumber_set(number v) {
    this->numberobj_01_value_set(v);
}

void notein_01_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (channel == this->notein_01_channel || this->notein_01_channel <= 0) {
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

void ctlin_01_outchannel_set(number ) {}

void ctlin_01_outcontroller_set(number ) {}

void fromnormalized_01_output_set(number v) {
    this->param_01_value_set(v);
}

void fromnormalized_01_input_set(number v) {
    this->fromnormalized_01_output_set(this->fromnormalized(0, v));
}

void expr_02_out1_set(number v) {
    this->expr_02_out1 = v;
    this->fromnormalized_01_input_set(this->expr_02_out1);
}

void expr_02_in1_set(number in1) {
    this->expr_02_in1 = in1;
    this->expr_02_out1_set(this->expr_02_in1 * this->expr_02_in2);//#map:expr_02:1
}

void ctlin_01_value_set(number v) {
    this->expr_02_in1_set(v);
}

void ctlin_01_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_01_channel || this->ctlin_01_channel == -1) && (data[1] == this->ctlin_01_controller || this->ctlin_01_controller == -1)) {
        this->ctlin_01_outchannel_set(channel);
        this->ctlin_01_outcontroller_set(data[1]);
        this->ctlin_01_value_set(data[2]);
        this->ctlin_01_status = 0;
    }
}

void ctlin_02_outchannel_set(number ) {}

void ctlin_02_outcontroller_set(number ) {}

void fromnormalized_02_output_set(number v) {
    this->param_02_value_set(v);
}

void fromnormalized_02_input_set(number v) {
    this->fromnormalized_02_output_set(this->fromnormalized(1, v));
}

void expr_03_out1_set(number v) {
    this->expr_03_out1 = v;
    this->fromnormalized_02_input_set(this->expr_03_out1);
}

void expr_03_in1_set(number in1) {
    this->expr_03_in1 = in1;
    this->expr_03_out1_set(this->expr_03_in1 * this->expr_03_in2);//#map:expr_03:1
}

void ctlin_02_value_set(number v) {
    this->expr_03_in1_set(v);
}

void ctlin_02_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_02_channel || this->ctlin_02_channel == -1) && (data[1] == this->ctlin_02_controller || this->ctlin_02_controller == -1)) {
        this->ctlin_02_outchannel_set(channel);
        this->ctlin_02_outcontroller_set(data[1]);
        this->ctlin_02_value_set(data[2]);
        this->ctlin_02_status = 0;
    }
}

void ctlin_03_outchannel_set(number ) {}

void ctlin_03_outcontroller_set(number ) {}

void fromnormalized_03_output_set(number v) {
    this->param_03_value_set(v);
}

void fromnormalized_03_input_set(number v) {
    this->fromnormalized_03_output_set(this->fromnormalized(2, v));
}

void expr_04_out1_set(number v) {
    this->expr_04_out1 = v;
    this->fromnormalized_03_input_set(this->expr_04_out1);
}

void expr_04_in1_set(number in1) {
    this->expr_04_in1 = in1;
    this->expr_04_out1_set(this->expr_04_in1 * this->expr_04_in2);//#map:expr_04:1
}

void ctlin_03_value_set(number v) {
    this->expr_04_in1_set(v);
}

void ctlin_03_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_03_channel || this->ctlin_03_channel == -1) && (data[1] == this->ctlin_03_controller || this->ctlin_03_controller == -1)) {
        this->ctlin_03_outchannel_set(channel);
        this->ctlin_03_outcontroller_set(data[1]);
        this->ctlin_03_value_set(data[2]);
        this->ctlin_03_status = 0;
    }
}

void ctlin_04_outchannel_set(number ) {}

void ctlin_04_outcontroller_set(number ) {}

void fromnormalized_04_output_set(number v) {
    this->param_04_value_set(v);
}

void fromnormalized_04_input_set(number v) {
    this->fromnormalized_04_output_set(this->fromnormalized(3, v));
}

void expr_05_out1_set(number v) {
    this->expr_05_out1 = v;
    this->fromnormalized_04_input_set(this->expr_05_out1);
}

void expr_05_in1_set(number in1) {
    this->expr_05_in1 = in1;
    this->expr_05_out1_set(this->expr_05_in1 * this->expr_05_in2);//#map:expr_05:1
}

void ctlin_04_value_set(number v) {
    this->expr_05_in1_set(v);
}

void ctlin_04_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_04_channel || this->ctlin_04_channel == -1) && (data[1] == this->ctlin_04_controller || this->ctlin_04_controller == -1)) {
        this->ctlin_04_outchannel_set(channel);
        this->ctlin_04_outcontroller_set(data[1]);
        this->ctlin_04_value_set(data[2]);
        this->ctlin_04_status = 0;
    }
}

void ctlin_05_outchannel_set(number ) {}

void ctlin_05_outcontroller_set(number ) {}

void fromnormalized_05_output_set(number v) {
    this->param_05_value_set(v);
}

void fromnormalized_05_input_set(number v) {
    this->fromnormalized_05_output_set(this->fromnormalized(4, v));
}

void expr_09_out1_set(number v) {
    this->expr_09_out1 = v;
    this->fromnormalized_05_input_set(this->expr_09_out1);
}

void expr_09_in1_set(number in1) {
    this->expr_09_in1 = in1;
    this->expr_09_out1_set(this->expr_09_in1 * this->expr_09_in2);//#map:expr_09:1
}

void ctlin_05_value_set(number v) {
    this->expr_09_in1_set(v);
}

void ctlin_05_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_05_channel || this->ctlin_05_channel == -1) && (data[1] == this->ctlin_05_controller || this->ctlin_05_controller == -1)) {
        this->ctlin_05_outchannel_set(channel);
        this->ctlin_05_outcontroller_set(data[1]);
        this->ctlin_05_value_set(data[2]);
        this->ctlin_05_status = 0;
    }
}

void ctlin_06_outchannel_set(number ) {}

void ctlin_06_outcontroller_set(number ) {}

void fromnormalized_06_output_set(number v) {
    this->param_06_value_set(v);
}

void fromnormalized_06_input_set(number v) {
    this->fromnormalized_06_output_set(this->fromnormalized(5, v));
}

void expr_10_out1_set(number v) {
    this->expr_10_out1 = v;
    this->fromnormalized_06_input_set(this->expr_10_out1);
}

void expr_10_in1_set(number in1) {
    this->expr_10_in1 = in1;
    this->expr_10_out1_set(this->expr_10_in1 * this->expr_10_in2);//#map:expr_10:1
}

void ctlin_06_value_set(number v) {
    this->expr_10_in1_set(v);
}

void ctlin_06_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_06_channel || this->ctlin_06_channel == -1) && (data[1] == this->ctlin_06_controller || this->ctlin_06_controller == -1)) {
        this->ctlin_06_outchannel_set(channel);
        this->ctlin_06_outcontroller_set(data[1]);
        this->ctlin_06_value_set(data[2]);
        this->ctlin_06_status = 0;
    }
}

void ctlin_07_outchannel_set(number ) {}

void ctlin_07_outcontroller_set(number ) {}

void fromnormalized_07_output_set(number v) {
    this->param_07_value_set(v);
}

void fromnormalized_07_input_set(number v) {
    this->fromnormalized_07_output_set(this->fromnormalized(6, v));
}

void expr_11_out1_set(number v) {
    this->expr_11_out1 = v;
    this->fromnormalized_07_input_set(this->expr_11_out1);
}

void expr_11_in1_set(number in1) {
    this->expr_11_in1 = in1;
    this->expr_11_out1_set(this->expr_11_in1 * this->expr_11_in2);//#map:expr_11:1
}

void ctlin_07_value_set(number v) {
    this->expr_11_in1_set(v);
}

void ctlin_07_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_07_channel || this->ctlin_07_channel == -1) && (data[1] == this->ctlin_07_controller || this->ctlin_07_controller == -1)) {
        this->ctlin_07_outchannel_set(channel);
        this->ctlin_07_outcontroller_set(data[1]);
        this->ctlin_07_value_set(data[2]);
        this->ctlin_07_status = 0;
    }
}

void ctlin_08_outchannel_set(number ) {}

void ctlin_08_outcontroller_set(number ) {}

void fromnormalized_08_output_set(number v) {
    this->param_08_value_set(v);
}

void fromnormalized_08_input_set(number v) {
    this->fromnormalized_08_output_set(this->fromnormalized(7, v));
}

void expr_12_out1_set(number v) {
    this->expr_12_out1 = v;
    this->fromnormalized_08_input_set(this->expr_12_out1);
}

void expr_12_in1_set(number in1) {
    this->expr_12_in1 = in1;
    this->expr_12_out1_set(this->expr_12_in1 * this->expr_12_in2);//#map:expr_12:1
}

void ctlin_08_value_set(number v) {
    this->expr_12_in1_set(v);
}

void ctlin_08_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_08_channel || this->ctlin_08_channel == -1) && (data[1] == this->ctlin_08_controller || this->ctlin_08_controller == -1)) {
        this->ctlin_08_outchannel_set(channel);
        this->ctlin_08_outcontroller_set(data[1]);
        this->ctlin_08_value_set(data[2]);
        this->ctlin_08_status = 0;
    }
}

void ctlin_09_outchannel_set(number ) {}

void ctlin_09_outcontroller_set(number ) {}

void fromnormalized_09_output_set(number v) {
    this->param_09_value_set(v);
}

void fromnormalized_09_input_set(number v) {
    this->fromnormalized_09_output_set(this->fromnormalized(8, v));
}

void expr_13_out1_set(number v) {
    this->expr_13_out1 = v;
    this->fromnormalized_09_input_set(this->expr_13_out1);
}

void expr_13_in1_set(number in1) {
    this->expr_13_in1 = in1;
    this->expr_13_out1_set(this->expr_13_in1 * this->expr_13_in2);//#map:expr_13:1
}

void ctlin_09_value_set(number v) {
    this->expr_13_in1_set(v);
}

void ctlin_09_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_09_channel || this->ctlin_09_channel == -1) && (data[1] == this->ctlin_09_controller || this->ctlin_09_controller == -1)) {
        this->ctlin_09_outchannel_set(channel);
        this->ctlin_09_outcontroller_set(data[1]);
        this->ctlin_09_value_set(data[2]);
        this->ctlin_09_status = 0;
    }
}

void ctlin_10_outchannel_set(number ) {}

void ctlin_10_outcontroller_set(number ) {}

void fromnormalized_10_output_set(number v) {
    this->param_10_value_set(v);
}

void fromnormalized_10_input_set(number v) {
    this->fromnormalized_10_output_set(this->fromnormalized(9, v));
}

void expr_15_out1_set(number v) {
    this->expr_15_out1 = v;
    this->fromnormalized_10_input_set(this->expr_15_out1);
}

void expr_15_in1_set(number in1) {
    this->expr_15_in1 = in1;
    this->expr_15_out1_set(this->expr_15_in1 * this->expr_15_in2);//#map:expr_15:1
}

void ctlin_10_value_set(number v) {
    this->expr_15_in1_set(v);
}

void ctlin_10_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_10_channel || this->ctlin_10_channel == -1) && (data[1] == this->ctlin_10_controller || this->ctlin_10_controller == -1)) {
        this->ctlin_10_outchannel_set(channel);
        this->ctlin_10_outcontroller_set(data[1]);
        this->ctlin_10_value_set(data[2]);
        this->ctlin_10_status = 0;
    }
}

void ctlin_11_outchannel_set(number ) {}

void ctlin_11_outcontroller_set(number ) {}

void fromnormalized_11_output_set(number v) {
    this->param_11_value_set(v);
}

void fromnormalized_11_input_set(number v) {
    this->fromnormalized_11_output_set(this->fromnormalized(10, v));
}

void expr_16_out1_set(number v) {
    this->expr_16_out1 = v;
    this->fromnormalized_11_input_set(this->expr_16_out1);
}

void expr_16_in1_set(number in1) {
    this->expr_16_in1 = in1;
    this->expr_16_out1_set(this->expr_16_in1 * this->expr_16_in2);//#map:expr_16:1
}

void ctlin_11_value_set(number v) {
    this->expr_16_in1_set(v);
}

void ctlin_11_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_11_channel || this->ctlin_11_channel == -1) && (data[1] == this->ctlin_11_controller || this->ctlin_11_controller == -1)) {
        this->ctlin_11_outchannel_set(channel);
        this->ctlin_11_outcontroller_set(data[1]);
        this->ctlin_11_value_set(data[2]);
        this->ctlin_11_status = 0;
    }
}

void ctlin_12_outchannel_set(number ) {}

void ctlin_12_outcontroller_set(number ) {}

void fromnormalized_12_output_set(number v) {
    this->param_12_value_set(v);
}

void fromnormalized_12_input_set(number v) {
    this->fromnormalized_12_output_set(this->fromnormalized(11, v));
}

void expr_17_out1_set(number v) {
    this->expr_17_out1 = v;
    this->fromnormalized_12_input_set(this->expr_17_out1);
}

void expr_17_in1_set(number in1) {
    this->expr_17_in1 = in1;
    this->expr_17_out1_set(this->expr_17_in1 * this->expr_17_in2);//#map:expr_17:1
}

void ctlin_12_value_set(number v) {
    this->expr_17_in1_set(v);
}

void ctlin_12_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_12_channel || this->ctlin_12_channel == -1) && (data[1] == this->ctlin_12_controller || this->ctlin_12_controller == -1)) {
        this->ctlin_12_outchannel_set(channel);
        this->ctlin_12_outcontroller_set(data[1]);
        this->ctlin_12_value_set(data[2]);
        this->ctlin_12_status = 0;
    }
}

void ctlin_13_outchannel_set(number ) {}

void ctlin_13_outcontroller_set(number ) {}

void fromnormalized_13_output_set(number v) {
    this->param_13_value_set(v);
}

void fromnormalized_13_input_set(number v) {
    this->fromnormalized_13_output_set(this->fromnormalized(12, v));
}

void expr_18_out1_set(number v) {
    this->expr_18_out1 = v;
    this->fromnormalized_13_input_set(this->expr_18_out1);
}

void expr_18_in1_set(number in1) {
    this->expr_18_in1 = in1;
    this->expr_18_out1_set(this->expr_18_in1 * this->expr_18_in2);//#map:expr_18:1
}

void ctlin_13_value_set(number v) {
    this->expr_18_in1_set(v);
}

void ctlin_13_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_13_channel || this->ctlin_13_channel == -1) && (data[1] == this->ctlin_13_controller || this->ctlin_13_controller == -1)) {
        this->ctlin_13_outchannel_set(channel);
        this->ctlin_13_outcontroller_set(data[1]);
        this->ctlin_13_value_set(data[2]);
        this->ctlin_13_status = 0;
    }
}

void ctlin_14_outchannel_set(number ) {}

void ctlin_14_outcontroller_set(number ) {}

void fromnormalized_14_output_set(number v) {
    this->param_14_value_set(v);
}

void fromnormalized_14_input_set(number v) {
    this->fromnormalized_14_output_set(this->fromnormalized(13, v));
}

void expr_19_out1_set(number v) {
    this->expr_19_out1 = v;
    this->fromnormalized_14_input_set(this->expr_19_out1);
}

void expr_19_in1_set(number in1) {
    this->expr_19_in1 = in1;
    this->expr_19_out1_set(this->expr_19_in1 * this->expr_19_in2);//#map:expr_19:1
}

void ctlin_14_value_set(number v) {
    this->expr_19_in1_set(v);
}

void ctlin_14_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_14_channel || this->ctlin_14_channel == -1) && (data[1] == this->ctlin_14_controller || this->ctlin_14_controller == -1)) {
        this->ctlin_14_outchannel_set(channel);
        this->ctlin_14_outcontroller_set(data[1]);
        this->ctlin_14_value_set(data[2]);
        this->ctlin_14_status = 0;
    }
}

void ctlin_15_outchannel_set(number ) {}

void ctlin_15_outcontroller_set(number ) {}

void fromnormalized_15_output_set(number v) {
    this->param_15_value_set(v);
}

void fromnormalized_15_input_set(number v) {
    this->fromnormalized_15_output_set(this->fromnormalized(14, v));
}

void expr_20_out1_set(number v) {
    this->expr_20_out1 = v;
    this->fromnormalized_15_input_set(this->expr_20_out1);
}

void expr_20_in1_set(number in1) {
    this->expr_20_in1 = in1;
    this->expr_20_out1_set(this->expr_20_in1 * this->expr_20_in2);//#map:expr_20:1
}

void ctlin_15_value_set(number v) {
    this->expr_20_in1_set(v);
}

void ctlin_15_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_15_channel || this->ctlin_15_channel == -1) && (data[1] == this->ctlin_15_controller || this->ctlin_15_controller == -1)) {
        this->ctlin_15_outchannel_set(channel);
        this->ctlin_15_outcontroller_set(data[1]);
        this->ctlin_15_value_set(data[2]);
        this->ctlin_15_status = 0;
    }
}

void ctlin_16_outchannel_set(number ) {}

void ctlin_16_outcontroller_set(number ) {}

void fromnormalized_16_output_set(number v) {
    this->param_16_value_set(v);
}

void fromnormalized_16_input_set(number v) {
    this->fromnormalized_16_output_set(this->fromnormalized(15, v));
}

void expr_21_out1_set(number v) {
    this->expr_21_out1 = v;
    this->fromnormalized_16_input_set(this->expr_21_out1);
}

void expr_21_in1_set(number in1) {
    this->expr_21_in1 = in1;
    this->expr_21_out1_set(this->expr_21_in1 * this->expr_21_in2);//#map:expr_21:1
}

void ctlin_16_value_set(number v) {
    this->expr_21_in1_set(v);
}

void ctlin_16_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_16_channel || this->ctlin_16_channel == -1) && (data[1] == this->ctlin_16_controller || this->ctlin_16_controller == -1)) {
        this->ctlin_16_outchannel_set(channel);
        this->ctlin_16_outcontroller_set(data[1]);
        this->ctlin_16_value_set(data[2]);
        this->ctlin_16_status = 0;
    }
}

void ctlin_17_outchannel_set(number ) {}

void ctlin_17_outcontroller_set(number ) {}

void fromnormalized_17_output_set(number v) {
    this->param_17_value_set(v);
}

void fromnormalized_17_input_set(number v) {
    this->fromnormalized_17_output_set(this->fromnormalized(16, v));
}

void expr_22_out1_set(number v) {
    this->expr_22_out1 = v;
    this->fromnormalized_17_input_set(this->expr_22_out1);
}

void expr_22_in1_set(number in1) {
    this->expr_22_in1 = in1;
    this->expr_22_out1_set(this->expr_22_in1 * this->expr_22_in2);//#map:expr_22:1
}

void ctlin_17_value_set(number v) {
    this->expr_22_in1_set(v);
}

void ctlin_17_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_17_channel || this->ctlin_17_channel == -1) && (data[1] == this->ctlin_17_controller || this->ctlin_17_controller == -1)) {
        this->ctlin_17_outchannel_set(channel);
        this->ctlin_17_outcontroller_set(data[1]);
        this->ctlin_17_value_set(data[2]);
        this->ctlin_17_status = 0;
    }
}

void gen_01_perform(
    number in1,
    number terms,
    number filterOnOff,
    number cutoffOvertone,
    number attenuation,
    number ocillator,
    number PosNeg,
    number PosNegSync,
    number cycleCountToAdd,
    number cycleCountToSubtract,
    number termsToAddPerCount,
    number harmonicSeriesMode,
    number harmonicRatio,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    auto __gen_01_sampleCount_value = this->gen_01_sampleCount_value;
    Index i0;

    for (i0 = 0; i0 < (Index)n; i0++) {
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

        number posFilterOnOff = 0;
        auto result_0 = this->peek_default(this->gen_01_manageParam, 1, 0);
        posFilterOnOff = result_0[0];
        number posCutoffOvertone = 0;
        auto result_1 = this->peek_default(this->gen_01_manageParam, 2, 0);
        posCutoffOvertone = result_1[0];
        number posAttenuation = 0;
        auto result_2 = this->peek_default(this->gen_01_manageParam, 3, 0);
        posAttenuation = result_2[0];
        number posOcillator = 0;
        auto result_3 = this->peek_default(this->gen_01_manageParam, 4, 0);
        posOcillator = result_3[0];
        number negFilterOnOff = 0;
        auto result_4 = this->peek_default(this->gen_01_manageParam, 6, 0);
        negFilterOnOff = result_4[0];
        number negCutoffOvertone = 0;
        auto result_5 = this->peek_default(this->gen_01_manageParam, 7, 0);
        negCutoffOvertone = result_5[0];
        number negAttenuation = 0;
        auto result_6 = this->peek_default(this->gen_01_manageParam, 8, 0);
        negAttenuation = result_6[0];
        number negOcillator = 0;
        auto result_7 = this->peek_default(this->gen_01_manageParam, 9, 0);
        negOcillator = result_7[0];

        if (this->gen_01_change_8_next(cycleCountToAdd) != 0 || this->gen_01_change_9_next(cycleCountToSubtract) != 0 || this->gen_01_change_10_next(terms) != 0) {
            __gen_01_sampleCount_value = 0;
        }

        number periodSamps1_12 = (this->gen_01_mtof_11_next(in1, 440) == 0. ? 0. : this->sr / this->gen_01_mtof_11_next(in1, 440));
        number periodSamps2_13 = this->sr / (number)1;
        __gen_01_sampleCount_value = __gen_01_sampleCount_value + 1;
        number changeCycleNumber_15 = 0;
        number changeCycleNumber_14 = 0;

        {
            auto termsToAddPerCount_21 = termsToAddPerCount;
            auto cycleCountToSubtract_20 = cycleCountToSubtract;
            auto cycleCountToAdd_19 = cycleCountToAdd;
            auto manageParam_18 = this->gen_01_manageParam;
            auto sampleCount_17 = __gen_01_sampleCount_value;
            auto periodSamps_16 = periodSamps1_12;

            auto cycleCount_22 = this->wrap(
                sampleCount_17,
                0,
                periodSamps_16 * (cycleCountToAdd_19 + cycleCountToSubtract_20)
            );

            number cycleCount_1_23 = this->intnum((periodSamps_16 == 0. ? 0. : cycleCount_22 / periodSamps_16)) + 1;
            number posTerms_24 = 0;
            number negTerms_25 = 0;

            if (cycleCountToAdd_19 != 0 && cycleCount_1_23 <= cycleCountToAdd_19) {
                number peek_2 = 0;
                number peek_3 = 0;
                auto result_26 = this->peek_default(manageParam_18, 0, 0);
                peek_3 = result_26[1];
                peek_2 = result_26[0];
                posTerms_24 = peek_2 + cycleCount_1_23 * termsToAddPerCount_21;
                number peek_4 = 0;
                number peek_5 = 0;
                auto result_27 = this->peek_default(manageParam_18, 5, 0);
                peek_5 = result_27[1];
                peek_4 = result_27[0];
                negTerms_25 = peek_4 + cycleCount_1_23 * termsToAddPerCount_21;
            } else if (cycleCountToAdd_19 != 0 && cycleCount_1_23 > cycleCountToAdd_19) {
                number totalAddedTerms_28 = cycleCountToAdd_19 * termsToAddPerCount_21;
                number termsToSubtractPerCount_29 = (cycleCountToSubtract_20 == 0. ? 0. : totalAddedTerms_28 / cycleCountToSubtract_20);
                number countForSubtract_30 = cycleCount_1_23 - cycleCountToAdd_19;
                auto addedTerms_31 = this->intnum(totalAddedTerms_28 - termsToSubtractPerCount_29 * countForSubtract_30);

                if (posTerms_24 <= 0) {
                    posTerms_24 = 1;
                }

                if (negTerms_25 <= 0) {
                    negTerms_25 = 1;
                }

                number peek_6 = 0;
                number peek_7 = 0;
                auto result_32 = this->peek_default(manageParam_18, 0, 0);
                peek_7 = result_32[1];
                peek_6 = result_32[0];
                posTerms_24 = peek_6 + addedTerms_31;
                number peek_8 = 0;
                number peek_9 = 0;
                auto result_33 = this->peek_default(manageParam_18, 5, 0);
                peek_9 = result_33[1];
                peek_8 = result_33[0];
                negTerms_25 = peek_8 + addedTerms_31;
            } else {
                auto result_34 = this->peek_default(manageParam_18, 0, 0);
                posTerms_24 = result_34[0];
                auto result_35 = this->peek_default(manageParam_18, 5, 0);
                negTerms_25 = result_35[0];
            }

            {
                changeCycleNumber_14 = posTerms_24;
                changeCycleNumber_15 = negTerms_25;
            }
        }

        number posTerms1 = 0;
        number negTerms1 = 0;
        posTerms1 = changeCycleNumber_14, negTerms1 = changeCycleNumber_15;
        number changeCycleNumber_37 = 0;
        number changeCycleNumber_36 = 0;

        {
            auto termsToAddPerCount_43 = termsToAddPerCount;
            auto cycleCountToSubtract_42 = cycleCountToSubtract;
            auto cycleCountToAdd_41 = cycleCountToAdd;
            auto manageParam_40 = this->gen_01_manageParam;
            auto sampleCount_39 = __gen_01_sampleCount_value;
            auto periodSamps_38 = periodSamps2_13;

            auto cycleCount_44 = this->wrap(
                sampleCount_39,
                0,
                periodSamps_38 * (cycleCountToAdd_41 + cycleCountToSubtract_42)
            );

            number cycleCount_1_45 = this->intnum((periodSamps_38 == 0. ? 0. : cycleCount_44 / periodSamps_38)) + 1;
            number posTerms_46 = 0;
            number negTerms_47 = 0;

            if (cycleCountToAdd_41 != 0 && cycleCount_1_45 <= cycleCountToAdd_41) {
                number peek_2 = 0;
                number peek_3 = 0;
                auto result_48 = this->peek_default(manageParam_40, 0, 0);
                peek_3 = result_48[1];
                peek_2 = result_48[0];
                posTerms_46 = peek_2 + cycleCount_1_45 * termsToAddPerCount_43;
                number peek_4 = 0;
                number peek_5 = 0;
                auto result_49 = this->peek_default(manageParam_40, 5, 0);
                peek_5 = result_49[1];
                peek_4 = result_49[0];
                negTerms_47 = peek_4 + cycleCount_1_45 * termsToAddPerCount_43;
            } else if (cycleCountToAdd_41 != 0 && cycleCount_1_45 > cycleCountToAdd_41) {
                number totalAddedTerms_50 = cycleCountToAdd_41 * termsToAddPerCount_43;
                number termsToSubtractPerCount_51 = (cycleCountToSubtract_42 == 0. ? 0. : totalAddedTerms_50 / cycleCountToSubtract_42);
                number countForSubtract_52 = cycleCount_1_45 - cycleCountToAdd_41;
                auto addedTerms_53 = this->intnum(totalAddedTerms_50 - termsToSubtractPerCount_51 * countForSubtract_52);

                if (posTerms_46 <= 0) {
                    posTerms_46 = 1;
                }

                if (negTerms_47 <= 0) {
                    negTerms_47 = 1;
                }

                number peek_6 = 0;
                number peek_7 = 0;
                auto result_54 = this->peek_default(manageParam_40, 0, 0);
                peek_7 = result_54[1];
                peek_6 = result_54[0];
                posTerms_46 = peek_6 + addedTerms_53;
                number peek_8 = 0;
                number peek_9 = 0;
                auto result_55 = this->peek_default(manageParam_40, 5, 0);
                peek_9 = result_55[1];
                peek_8 = result_55[0];
                negTerms_47 = peek_8 + addedTerms_53;
            } else {
                auto result_56 = this->peek_default(manageParam_40, 0, 0);
                posTerms_46 = result_56[0];
                auto result_57 = this->peek_default(manageParam_40, 5, 0);
                negTerms_47 = result_57[0];
            }

            {
                changeCycleNumber_36 = posTerms_46;
                changeCycleNumber_37 = negTerms_47;
            }
        }

        number posTerms2 = 0;
        number negTerms2 = 0;
        posTerms2 = changeCycleNumber_36, negTerms2 = changeCycleNumber_37;
        auto maxTerms1_58 = this->maximum(posTerms1, negTerms1);
        auto maxTerms2_59 = this->maximum(posTerms2, negTerms2);
        auto maxTerms_60 = this->maximum(maxTerms1_58, maxTerms2_59);
        number posWave1_61 = 0;
        number negWave1_62 = 0;
        number currentFreq1_63 = 0;
        number posWave2_64 = 0;
        number negWave2_65 = 0;
        number currentFreq2_66 = 0;
        number step_67 = (this->sr == 0. ? 0. : (number)1 / this->sr);
        number phaseReset1_68 = 1;
        number phaseReset2_69 = 1;

        for (number i = 1; i <= maxTerms_60; i = i + 1) {
            if (this->gen_01_change_70_next(terms) != 0 || (bool)(this->gen_01_change_71_next(maxTerms1_58)) || (bool)(this->gen_01_change_72_next(harmonicRatio)) || (bool)(this->gen_01_change_73_next(harmonicSeriesMode))) {
                phaseReset1_68 = 0;
            }

            if (this->gen_01_change_74_next(terms) != 0 || (bool)(this->gen_01_change_75_next(maxTerms2_59)) || (bool)(this->gen_01_change_76_next(harmonicRatio)) || (bool)(this->gen_01_change_77_next(harmonicSeriesMode))) {
                phaseReset2_69 = 0;
            }

            if (harmonicSeriesMode == 0) {
                currentFreq1_63 = this->gen_01_mtof_78_next(in1, 440) * (1 + (i - 1) * harmonicRatio);
                currentFreq2_66 = 1 * (1 + (i - 1) * harmonicRatio);
            } else {
                currentFreq1_63 = this->gen_01_mtof_79_next(in1, 440) * fixnan(rnbo_pow(harmonicRatio, i - 1));
                currentFreq2_66 = 1 * fixnan(rnbo_pow(harmonicRatio, i - 1));
            }

            number processSynthesis_81 = 0;
            number processSynthesis_80 = 0;

            {
                auto phaseStoreCh_99 = 0;
                auto negOcillator_98 = negOcillator;
                auto negAttenuation_97 = negAttenuation;
                auto negCutoffOvertone_96 = negCutoffOvertone;
                auto negFilterOnOff_95 = negFilterOnOff;
                auto posOcillator_94 = posOcillator;
                auto posAttenuation_93 = posAttenuation;
                auto posCutoffOvertone_92 = posCutoffOvertone;
                auto posFilterOnOff_91 = posFilterOnOff;
                auto phaseReset_90 = phaseReset1_68;
                auto phaseStore_89 = this->gen_01_phaseStore;
                auto step_88 = step_67;
                auto negTerms_87 = negTerms1;
                auto posTerms_86 = posTerms1;
                auto negWave_85 = negWave1_62;
                auto posWave_84 = posWave1_61;
                auto currentFreq_83 = currentFreq1_63;
                auto index_82 = i;
                number lastPhase = 0;
                auto result_100 = this->peek_default(phaseStore_89, index_82 - 1, phaseStoreCh_99);
                lastPhase = result_100[0];
                number phaseToAdv_101 = 6.28318530717958647692 * currentFreq_83 * step_88;
                number newPhase_102 = this->wrap(lastPhase + phaseToAdv_101, 0, 6.28318530717958647692) * phaseReset_90;
                this->poke_default(phaseStore_89, newPhase_102, index_82 - 1, phaseStoreCh_99, 0);
                number sine_wave_103 = rnbo_sin(newPhase_102);

                if (index_82 <= posTerms_86) {
                    number fourierSeriesCalculation_104 = 0;

                    {
                        auto Ocillator_110 = posOcillator_94;
                        auto Attenuation_109 = posAttenuation_93;
                        auto CutoffOvertone_108 = posCutoffOvertone_92;
                        auto FilterOnOff_107 = posFilterOnOff_91;
                        auto index_106 = index_82;
                        auto currentFreq_105 = currentFreq_83;
                        number Factors_111 = 1;
                        number Amp_filter_112 = 1;

                        if (Ocillator_110 == 1) {
                            if (this->safemod(index_106, 2) == 1) {
                                Factors_111 = (3.14159265358979323846 * index_106 == 0. ? 0. : (number)4 / (3.14159265358979323846 * index_106));
                            } else {
                                Factors_111 = 0;
                            }
                        } else if (Ocillator_110 == 2) {
                            if (this->safemod(index_106, 2) == 1) {
                                number myTriangle_113 = 0;

                                {
                                    auto n2_114 = index_106;
                                    number amp_factor2_115 = (fixnan(rnbo_pow(3.14159265358979323846, 2)) * fixnan(rnbo_pow(n2_114, 2)) == 0. ? 0. : (number)8 / (fixnan(rnbo_pow(3.14159265358979323846, 2)) * fixnan(rnbo_pow(n2_114, 2))));
                                    number phase_factor2_116 = fixnan(rnbo_pow(-1, (n2_114 - 1) / (number)2));
                                    myTriangle_113 = amp_factor2_115 * phase_factor2_116;
                                }

                                Factors_111 = myTriangle_113;
                            } else {
                                Factors_111 = 0;
                            }
                        } else {
                            number mySawtooth_117 = 0;

                            {
                                auto n3_118 = index_106;
                                number amp_factor3_119 = (3.14159265358979323846 * n3_118 == 0. ? 0. : (number)2 / (3.14159265358979323846 * n3_118));
                                number phase_factor3_120 = fixnan(rnbo_pow(-1, n3_118 + 1));
                                mySawtooth_117 = amp_factor3_119 * phase_factor3_120;
                            }

                            Factors_111 = mySawtooth_117;
                        }

                        if (FilterOnOff_107 == 1) {
                            if (index_106 >= CutoffOvertone_108) {
                                number n_overtone_121 = (index_106 - CutoffOvertone_108 + 1) * Attenuation_109;
                                Amp_filter_112 = (n_overtone_121 == 0. ? 0. : (number)1 / n_overtone_121);
                            }
                        }

                        if (currentFreq_105 > this->sr / (number)2) {
                            Factors_111 = 0;
                        }

                        fourierSeriesCalculation_104 = Factors_111 * Amp_filter_112;
                    }

                    posWave_84 = posWave_84 + sine_wave_103 * fourierSeriesCalculation_104;
                }

                if (index_82 <= negTerms_87) {
                    number fourierSeriesCalculation_122 = 0;

                    {
                        auto Ocillator_128 = negOcillator_98;
                        auto Attenuation_127 = negAttenuation_97;
                        auto CutoffOvertone_126 = negCutoffOvertone_96;
                        auto FilterOnOff_125 = negFilterOnOff_95;
                        auto index_124 = index_82;
                        auto currentFreq_123 = currentFreq_83;
                        number Factors_129 = 1;
                        number Amp_filter_130 = 1;

                        if (Ocillator_128 == 1) {
                            if (this->safemod(index_124, 2) == 1) {
                                Factors_129 = (3.14159265358979323846 * index_124 == 0. ? 0. : (number)4 / (3.14159265358979323846 * index_124));
                            } else {
                                Factors_129 = 0;
                            }
                        } else if (Ocillator_128 == 2) {
                            if (this->safemod(index_124, 2) == 1) {
                                number myTriangle_131 = 0;

                                {
                                    auto n2_132 = index_124;
                                    number amp_factor2_133 = (fixnan(rnbo_pow(3.14159265358979323846, 2)) * fixnan(rnbo_pow(n2_132, 2)) == 0. ? 0. : (number)8 / (fixnan(rnbo_pow(3.14159265358979323846, 2)) * fixnan(rnbo_pow(n2_132, 2))));
                                    number phase_factor2_134 = fixnan(rnbo_pow(-1, (n2_132 - 1) / (number)2));
                                    myTriangle_131 = amp_factor2_133 * phase_factor2_134;
                                }

                                Factors_129 = myTriangle_131;
                            } else {
                                Factors_129 = 0;
                            }
                        } else {
                            number mySawtooth_135 = 0;

                            {
                                auto n3_136 = index_124;
                                number amp_factor3_137 = (3.14159265358979323846 * n3_136 == 0. ? 0. : (number)2 / (3.14159265358979323846 * n3_136));
                                number phase_factor3_138 = fixnan(rnbo_pow(-1, n3_136 + 1));
                                mySawtooth_135 = amp_factor3_137 * phase_factor3_138;
                            }

                            Factors_129 = mySawtooth_135;
                        }

                        if (FilterOnOff_125 == 1) {
                            if (index_124 >= CutoffOvertone_126) {
                                number n_overtone_139 = (index_124 - CutoffOvertone_126 + 1) * Attenuation_127;
                                Amp_filter_130 = (n_overtone_139 == 0. ? 0. : (number)1 / n_overtone_139);
                            }
                        }

                        if (currentFreq_123 > this->sr / (number)2) {
                            Factors_129 = 0;
                        }

                        fourierSeriesCalculation_122 = Factors_129 * Amp_filter_130;
                    }

                    negWave_85 = negWave_85 + sine_wave_103 * fourierSeriesCalculation_122;
                }

                {
                    processSynthesis_80 = posWave_84;
                    processSynthesis_81 = negWave_85;
                }
            }

            posWave1_61 = processSynthesis_80, negWave1_62 = processSynthesis_81;
            number processSynthesis_141 = 0;
            number processSynthesis_140 = 0;

            {
                auto phaseStoreCh_159 = 1;
                auto negOcillator_158 = negOcillator;
                auto negAttenuation_157 = negAttenuation;
                auto negCutoffOvertone_156 = negCutoffOvertone;
                auto negFilterOnOff_155 = negFilterOnOff;
                auto posOcillator_154 = posOcillator;
                auto posAttenuation_153 = posAttenuation;
                auto posCutoffOvertone_152 = posCutoffOvertone;
                auto posFilterOnOff_151 = posFilterOnOff;
                auto phaseReset_150 = phaseReset2_69;
                auto phaseStore_149 = this->gen_01_phaseStore;
                auto step_148 = step_67;
                auto negTerms_147 = negTerms2;
                auto posTerms_146 = posTerms2;
                auto negWave_145 = negWave2_65;
                auto posWave_144 = posWave2_64;
                auto currentFreq_143 = currentFreq2_66;
                auto index_142 = i;
                number lastPhase = 0;
                auto result_160 = this->peek_default(phaseStore_149, index_142 - 1, phaseStoreCh_159);
                lastPhase = result_160[0];
                number phaseToAdv_161 = 6.28318530717958647692 * currentFreq_143 * step_148;
                number newPhase_162 = this->wrap(lastPhase + phaseToAdv_161, 0, 6.28318530717958647692) * phaseReset_150;
                this->poke_default(phaseStore_149, newPhase_162, index_142 - 1, phaseStoreCh_159, 0);
                number sine_wave_163 = rnbo_sin(newPhase_162);

                if (index_142 <= posTerms_146) {
                    number fourierSeriesCalculation_164 = 0;

                    {
                        auto Ocillator_170 = posOcillator_154;
                        auto Attenuation_169 = posAttenuation_153;
                        auto CutoffOvertone_168 = posCutoffOvertone_152;
                        auto FilterOnOff_167 = posFilterOnOff_151;
                        auto index_166 = index_142;
                        auto currentFreq_165 = currentFreq_143;
                        number Factors_171 = 1;
                        number Amp_filter_172 = 1;

                        if (Ocillator_170 == 1) {
                            if (this->safemod(index_166, 2) == 1) {
                                Factors_171 = (3.14159265358979323846 * index_166 == 0. ? 0. : (number)4 / (3.14159265358979323846 * index_166));
                            } else {
                                Factors_171 = 0;
                            }
                        } else if (Ocillator_170 == 2) {
                            if (this->safemod(index_166, 2) == 1) {
                                number myTriangle_173 = 0;

                                {
                                    auto n2_174 = index_166;
                                    number amp_factor2_175 = (fixnan(rnbo_pow(3.14159265358979323846, 2)) * fixnan(rnbo_pow(n2_174, 2)) == 0. ? 0. : (number)8 / (fixnan(rnbo_pow(3.14159265358979323846, 2)) * fixnan(rnbo_pow(n2_174, 2))));
                                    number phase_factor2_176 = fixnan(rnbo_pow(-1, (n2_174 - 1) / (number)2));
                                    myTriangle_173 = amp_factor2_175 * phase_factor2_176;
                                }

                                Factors_171 = myTriangle_173;
                            } else {
                                Factors_171 = 0;
                            }
                        } else {
                            number mySawtooth_177 = 0;

                            {
                                auto n3_178 = index_166;
                                number amp_factor3_179 = (3.14159265358979323846 * n3_178 == 0. ? 0. : (number)2 / (3.14159265358979323846 * n3_178));
                                number phase_factor3_180 = fixnan(rnbo_pow(-1, n3_178 + 1));
                                mySawtooth_177 = amp_factor3_179 * phase_factor3_180;
                            }

                            Factors_171 = mySawtooth_177;
                        }

                        if (FilterOnOff_167 == 1) {
                            if (index_166 >= CutoffOvertone_168) {
                                number n_overtone_181 = (index_166 - CutoffOvertone_168 + 1) * Attenuation_169;
                                Amp_filter_172 = (n_overtone_181 == 0. ? 0. : (number)1 / n_overtone_181);
                            }
                        }

                        if (currentFreq_165 > this->sr / (number)2) {
                            Factors_171 = 0;
                        }

                        fourierSeriesCalculation_164 = Factors_171 * Amp_filter_172;
                    }

                    posWave_144 = posWave_144 + sine_wave_163 * fourierSeriesCalculation_164;
                }

                if (index_142 <= negTerms_147) {
                    number fourierSeriesCalculation_182 = 0;

                    {
                        auto Ocillator_188 = negOcillator_158;
                        auto Attenuation_187 = negAttenuation_157;
                        auto CutoffOvertone_186 = negCutoffOvertone_156;
                        auto FilterOnOff_185 = negFilterOnOff_155;
                        auto index_184 = index_142;
                        auto currentFreq_183 = currentFreq_143;
                        number Factors_189 = 1;
                        number Amp_filter_190 = 1;

                        if (Ocillator_188 == 1) {
                            if (this->safemod(index_184, 2) == 1) {
                                Factors_189 = (3.14159265358979323846 * index_184 == 0. ? 0. : (number)4 / (3.14159265358979323846 * index_184));
                            } else {
                                Factors_189 = 0;
                            }
                        } else if (Ocillator_188 == 2) {
                            if (this->safemod(index_184, 2) == 1) {
                                number myTriangle_191 = 0;

                                {
                                    auto n2_192 = index_184;
                                    number amp_factor2_193 = (fixnan(rnbo_pow(3.14159265358979323846, 2)) * fixnan(rnbo_pow(n2_192, 2)) == 0. ? 0. : (number)8 / (fixnan(rnbo_pow(3.14159265358979323846, 2)) * fixnan(rnbo_pow(n2_192, 2))));
                                    number phase_factor2_194 = fixnan(rnbo_pow(-1, (n2_192 - 1) / (number)2));
                                    myTriangle_191 = amp_factor2_193 * phase_factor2_194;
                                }

                                Factors_189 = myTriangle_191;
                            } else {
                                Factors_189 = 0;
                            }
                        } else {
                            number mySawtooth_195 = 0;

                            {
                                auto n3_196 = index_184;
                                number amp_factor3_197 = (3.14159265358979323846 * n3_196 == 0. ? 0. : (number)2 / (3.14159265358979323846 * n3_196));
                                number phase_factor3_198 = fixnan(rnbo_pow(-1, n3_196 + 1));
                                mySawtooth_195 = amp_factor3_197 * phase_factor3_198;
                            }

                            Factors_189 = mySawtooth_195;
                        }

                        if (FilterOnOff_185 == 1) {
                            if (index_184 >= CutoffOvertone_186) {
                                number n_overtone_199 = (index_184 - CutoffOvertone_186 + 1) * Attenuation_187;
                                Amp_filter_190 = (n_overtone_199 == 0. ? 0. : (number)1 / n_overtone_199);
                            }
                        }

                        if (currentFreq_183 > this->sr / (number)2) {
                            Factors_189 = 0;
                        }

                        fourierSeriesCalculation_182 = Factors_189 * Amp_filter_190;
                    }

                    negWave_145 = negWave_145 + sine_wave_163 * fourierSeriesCalculation_182;
                }

                {
                    processSynthesis_140 = posWave_144;
                    processSynthesis_141 = negWave_145;
                }
            }

            posWave2_64 = processSynthesis_140, negWave2_65 = processSynthesis_141;
        }

        if (posWave1_61 >= 0) {
            negWave1_62 = negWave1_62 * 0;
        } else {
            posWave1_61 = posWave1_61 * 0;
        }

        if (posWave2_64 >= 0) {
            negWave2_65 = negWave2_65 * 0;
        } else {
            posWave2_64 = posWave2_64 * 0;
        }

        number SynthesizedWave1_200 = negWave1_62 + posWave1_61;
        number SynthesizedWave2_201 = negWave2_65 + posWave2_64;
        number expr_10_202 = (SynthesizedWave1_200 * 0.7 > 1 ? 1 : (SynthesizedWave1_200 * 0.7 < -1 ? -1 : SynthesizedWave1_200 * 0.7));
        number expr_11_203 = (SynthesizedWave2_201 * 0.7 > 1 ? 1 : (SynthesizedWave2_201 * 0.7 < -1 ? -1 : SynthesizedWave2_201 * 0.7));
        out2[(Index)i0] = expr_11_203;
        out1[(Index)i0] = expr_10_202;
    }

    this->gen_01_sampleCount_value = __gen_01_sampleCount_value;
}

void delaytilde_01_perform(number delay, const SampleValue * input, SampleValue * output, Index n) {
    auto __delaytilde_01_crossfadeDelay = this->delaytilde_01_crossfadeDelay;
    auto __delaytilde_01_rampInSamples = this->delaytilde_01_rampInSamples;
    auto __delaytilde_01_ramp = this->delaytilde_01_ramp;
    auto __delaytilde_01_lastDelay = this->delaytilde_01_lastDelay;

    for (Index i = 0; i < n; i++) {
        if (__delaytilde_01_lastDelay == -1) {
            __delaytilde_01_lastDelay = delay;
        }

        if (__delaytilde_01_ramp > 0) {
            number factor = __delaytilde_01_ramp / __delaytilde_01_rampInSamples;
            output[(Index)i] = this->delaytilde_01_del_read(__delaytilde_01_crossfadeDelay, 0) * factor + this->delaytilde_01_del_read(__delaytilde_01_lastDelay, 0) * (1. - factor);
            __delaytilde_01_ramp--;
        } else {
            number effectiveDelay = delay;

            if (effectiveDelay != __delaytilde_01_lastDelay) {
                __delaytilde_01_ramp = __delaytilde_01_rampInSamples;
                __delaytilde_01_crossfadeDelay = __delaytilde_01_lastDelay;
                __delaytilde_01_lastDelay = effectiveDelay;
                output[(Index)i] = this->delaytilde_01_del_read(__delaytilde_01_crossfadeDelay, 0);
                __delaytilde_01_ramp--;
            } else {
                output[(Index)i] = this->delaytilde_01_del_read(effectiveDelay, 0);
            }
        }

        this->delaytilde_01_del_write(input[(Index)i]);
        this->delaytilde_01_del_step();
    }

    this->delaytilde_01_lastDelay = __delaytilde_01_lastDelay;
    this->delaytilde_01_ramp = __delaytilde_01_ramp;
    this->delaytilde_01_crossfadeDelay = __delaytilde_01_crossfadeDelay;
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
    auto __adsr_01_maxsustain = this->adsr_01_maxsustain;
    auto __adsr_01_mspersamp = this->adsr_01_mspersamp;
    bool bangMute = false;

    for (Index i = 0; i < n; i++) {
        number clampedattack = (attack > __adsr_01_mspersamp ? attack : __adsr_01_mspersamp);
        number clampeddecay = (decay > __adsr_01_mspersamp ? decay : __adsr_01_mspersamp);
        number clampedsustain = (__adsr_01_maxsustain > __adsr_01_mspersamp ? __adsr_01_maxsustain : __adsr_01_mspersamp);
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
            __adsr_01_phase = 3;
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
        } else if (__adsr_01_phase == 3) {
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
                __adsr_01_phase = 1;
                __adsr_01_outval = __adsr_01_amplitude * sustain;
            } else {
                __adsr_01_outval = __adsr_01_amplitude * sustain + (__adsr_01_amplitude - __adsr_01_amplitude * sustain) * (1. - __adsr_01_time / clampeddecay);
            }
        } else if (__adsr_01_phase == 1) {
            if (__adsr_01_time > clampedsustain && __adsr_01_maxsustain > -1) {
                __adsr_01_time -= clampedsustain;
                __adsr_01_phase = 4;
                __adsr_01_amplitude = __adsr_01_outval;
            } else {
                __adsr_01_outval = __adsr_01_amplitude * sustain;
            }
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

void delaytilde_02_perform(number delay, const SampleValue * input, SampleValue * output, Index n) {
    auto __delaytilde_02_crossfadeDelay = this->delaytilde_02_crossfadeDelay;
    auto __delaytilde_02_rampInSamples = this->delaytilde_02_rampInSamples;
    auto __delaytilde_02_ramp = this->delaytilde_02_ramp;
    auto __delaytilde_02_lastDelay = this->delaytilde_02_lastDelay;

    for (Index i = 0; i < n; i++) {
        if (__delaytilde_02_lastDelay == -1) {
            __delaytilde_02_lastDelay = delay;
        }

        if (__delaytilde_02_ramp > 0) {
            number factor = __delaytilde_02_ramp / __delaytilde_02_rampInSamples;
            output[(Index)i] = this->delaytilde_02_del_read(__delaytilde_02_crossfadeDelay, 0) * factor + this->delaytilde_02_del_read(__delaytilde_02_lastDelay, 0) * (1. - factor);
            __delaytilde_02_ramp--;
        } else {
            number effectiveDelay = delay;

            if (effectiveDelay != __delaytilde_02_lastDelay) {
                __delaytilde_02_ramp = __delaytilde_02_rampInSamples;
                __delaytilde_02_crossfadeDelay = __delaytilde_02_lastDelay;
                __delaytilde_02_lastDelay = effectiveDelay;
                output[(Index)i] = this->delaytilde_02_del_read(__delaytilde_02_crossfadeDelay, 0);
                __delaytilde_02_ramp--;
            } else {
                output[(Index)i] = this->delaytilde_02_del_read(effectiveDelay, 0);
            }
        }

        this->delaytilde_02_del_write(input[(Index)i]);
        this->delaytilde_02_del_step();
    }

    this->delaytilde_02_lastDelay = __delaytilde_02_lastDelay;
    this->delaytilde_02_ramp = __delaytilde_02_ramp;
    this->delaytilde_02_crossfadeDelay = __delaytilde_02_crossfadeDelay;
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

void linetilde_02_perform(SampleValue * out, Index n) {
    auto __linetilde_02_time = this->linetilde_02_time;
    auto __linetilde_02_keepramp = this->linetilde_02_keepramp;
    auto __linetilde_02_currentValue = this->linetilde_02_currentValue;
    Index i = 0;

    if ((bool)(this->linetilde_02_activeRamps->length)) {
        while ((bool)(this->linetilde_02_activeRamps->length) && i < n) {
            number destinationValue = this->linetilde_02_activeRamps[0];
            number inc = this->linetilde_02_activeRamps[1];
            number rampTimeInSamples = this->linetilde_02_activeRamps[2] - this->audioProcessSampleCount - i;
            number val = __linetilde_02_currentValue;

            while (rampTimeInSamples > 0 && i < n) {
                out[(Index)i] = val;
                val += inc;
                i++;
                rampTimeInSamples--;
            }

            if (rampTimeInSamples <= 0) {
                val = destinationValue;
                this->linetilde_02_activeRamps->splice(0, 3);

                if ((bool)(!(bool)(this->linetilde_02_activeRamps->length))) {
                    this->getEngine()->scheduleClockEventWithValue(
                        this,
                        -281953904,
                        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                        0
                    );;

                    if ((bool)(!(bool)(__linetilde_02_keepramp))) {
                        __linetilde_02_time = 0;
                    }
                }
            }

            __linetilde_02_currentValue = val;
        }
    }

    while (i < n) {
        out[(Index)i] = __linetilde_02_currentValue;
        i++;
    }

    this->linetilde_02_currentValue = __linetilde_02_currentValue;
    this->linetilde_02_time = __linetilde_02_time;
}

void dspexpr_03_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_02_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_01_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void signalforwarder_01_perform(const SampleValue * input, SampleValue * output, Index n) {
    copySignal(output, input, n);
}

void signalforwarder_02_perform(const SampleValue * input, SampleValue * output, Index n) {
    copySignal(output, input, n);
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

void delaytilde_01_del_step() {
    this->delaytilde_01_del_reader++;

    if (this->delaytilde_01_del_reader >= (Int)(this->delaytilde_01_del_buffer->getSize()))
        this->delaytilde_01_del_reader = 0;
}

number delaytilde_01_del_read(number size, Int interp) {
    if (interp == 0) {
        number r = (Int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Int index2 = (Int)(index1 + 1);

        return this->linearinterp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    } else if (interp == 1) {
        number r = (Int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? 1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->cubicinterp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    } else if (interp == 6) {
        number r = (Int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? 1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->fastcubicinterp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    } else if (interp == 2) {
        number r = (Int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? 1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->splineinterp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    } else if (interp == 7) {
        number r = (Int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? 1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);
        Index index5 = (Index)(index4 + 1);
        Index index6 = (Index)(index5 + 1);

        return this->spline6interp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index5 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index6 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    } else if (interp == 3) {
        number r = (Int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);

        return this->cosineinterp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    }

    number r = (Int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->delaytilde_01_del_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
    );
}

void delaytilde_01_del_write(number v) {
    this->delaytilde_01_del_writer = this->delaytilde_01_del_reader;
    this->delaytilde_01_del_buffer[(Index)this->delaytilde_01_del_writer] = v;
}

number delaytilde_01_del_next(number v, Int size) {
    number effectiveSize = (size == -1 ? this->delaytilde_01_del__maxdelay : size);
    number val = this->delaytilde_01_del_read(effectiveSize, 0);
    this->delaytilde_01_del_write(v);
    this->delaytilde_01_del_step();
    return val;
}

array<Index, 2> delaytilde_01_del_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->delaytilde_01_del_evaluateSizeExpr(this->sr, this->vs);
        this->delaytilde_01_del_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void delaytilde_01_del_init() {
    auto result = this->delaytilde_01_del_calcSizeInSamples();
    this->delaytilde_01_del__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->delaytilde_01_del_buffer->requestSize(requestedSizeInSamples, 1);
    this->delaytilde_01_del_wrap = requestedSizeInSamples - 1;
}

void delaytilde_01_del_clear() {
    this->delaytilde_01_del_buffer->setZero();
}

void delaytilde_01_del_reset() {
    auto result = this->delaytilde_01_del_calcSizeInSamples();
    this->delaytilde_01_del__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->delaytilde_01_del_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->delaytilde_01_del_buffer);
    this->delaytilde_01_del_wrap = this->delaytilde_01_del_buffer->getSize() - 1;
    this->delaytilde_01_del_clear();

    if (this->delaytilde_01_del_reader >= this->delaytilde_01_del__maxdelay || this->delaytilde_01_del_writer >= this->delaytilde_01_del__maxdelay) {
        this->delaytilde_01_del_reader = 0;
        this->delaytilde_01_del_writer = 0;
    }
}

void delaytilde_01_del_dspsetup() {
    this->delaytilde_01_del_reset();
}

number delaytilde_01_del_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    return samplerate;
}

number delaytilde_01_del_size() {
    return this->delaytilde_01_del__maxdelay;
}

void delaytilde_01_dspsetup(bool force) {
    if ((bool)(this->delaytilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->delaytilde_01_rampInSamples = (Int)(this->mstosamps(50));
    this->delaytilde_01_lastDelay = -1;
    this->delaytilde_01_setupDone = true;
    this->delaytilde_01_del_dspsetup();
}

void numberobj_01_init() {
    this->numberobj_01_currentFormat = 6;
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

number gen_01_change_8_next(number x) {
    number temp = x - this->gen_01_change_8_prev;
    this->gen_01_change_8_prev = x;
    return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
}

void gen_01_change_8_init() {
    this->gen_01_change_8_prev = 0;
}

void gen_01_change_8_reset() {
    this->gen_01_change_8_prev = 0;
}

number gen_01_change_9_next(number x) {
    number temp = x - this->gen_01_change_9_prev;
    this->gen_01_change_9_prev = x;
    return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
}

void gen_01_change_9_init() {
    this->gen_01_change_9_prev = 0;
}

void gen_01_change_9_reset() {
    this->gen_01_change_9_prev = 0;
}

number gen_01_change_10_next(number x) {
    number temp = x - this->gen_01_change_10_prev;
    this->gen_01_change_10_prev = x;
    return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
}

void gen_01_change_10_init() {
    this->gen_01_change_10_prev = 0;
}

void gen_01_change_10_reset() {
    this->gen_01_change_10_prev = 0;
}

number gen_01_mtof_11_next(number midivalue, number tuning) {
    RNBO_UNUSED(tuning);

    if (midivalue == this->gen_01_mtof_11_lastInValue && 440 == this->gen_01_mtof_11_lastTuning)
        return this->gen_01_mtof_11_lastOutValue;

    this->gen_01_mtof_11_lastInValue = midivalue;
    this->gen_01_mtof_11_lastTuning = 440;
    number result = 0;

    {
        result = rnbo_exp(.057762265 * (midivalue - 69.0));
    }

    this->gen_01_mtof_11_lastOutValue = 440 * result;
    return this->gen_01_mtof_11_lastOutValue;
}

void gen_01_mtof_11_reset() {
    this->gen_01_mtof_11_lastInValue = 0;
    this->gen_01_mtof_11_lastOutValue = 0;
    this->gen_01_mtof_11_lastTuning = 0;
}

number gen_01_change_70_next(number x) {
    number temp = x - this->gen_01_change_70_prev;
    this->gen_01_change_70_prev = x;
    return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
}

void gen_01_change_70_init() {
    this->gen_01_change_70_prev = 0;
}

void gen_01_change_70_reset() {
    this->gen_01_change_70_prev = 0;
}

number gen_01_change_71_next(number x) {
    number temp = x - this->gen_01_change_71_prev;
    this->gen_01_change_71_prev = x;
    return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
}

void gen_01_change_71_init() {
    this->gen_01_change_71_prev = 0;
}

void gen_01_change_71_reset() {
    this->gen_01_change_71_prev = 0;
}

number gen_01_change_72_next(number x) {
    number temp = x - this->gen_01_change_72_prev;
    this->gen_01_change_72_prev = x;
    return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
}

void gen_01_change_72_init() {
    this->gen_01_change_72_prev = 0;
}

void gen_01_change_72_reset() {
    this->gen_01_change_72_prev = 0;
}

number gen_01_change_73_next(number x) {
    number temp = x - this->gen_01_change_73_prev;
    this->gen_01_change_73_prev = x;
    return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
}

void gen_01_change_73_init() {
    this->gen_01_change_73_prev = 0;
}

void gen_01_change_73_reset() {
    this->gen_01_change_73_prev = 0;
}

number gen_01_change_74_next(number x) {
    number temp = x - this->gen_01_change_74_prev;
    this->gen_01_change_74_prev = x;
    return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
}

void gen_01_change_74_init() {
    this->gen_01_change_74_prev = 0;
}

void gen_01_change_74_reset() {
    this->gen_01_change_74_prev = 0;
}

number gen_01_change_75_next(number x) {
    number temp = x - this->gen_01_change_75_prev;
    this->gen_01_change_75_prev = x;
    return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
}

void gen_01_change_75_init() {
    this->gen_01_change_75_prev = 0;
}

void gen_01_change_75_reset() {
    this->gen_01_change_75_prev = 0;
}

number gen_01_change_76_next(number x) {
    number temp = x - this->gen_01_change_76_prev;
    this->gen_01_change_76_prev = x;
    return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
}

void gen_01_change_76_init() {
    this->gen_01_change_76_prev = 0;
}

void gen_01_change_76_reset() {
    this->gen_01_change_76_prev = 0;
}

number gen_01_change_77_next(number x) {
    number temp = x - this->gen_01_change_77_prev;
    this->gen_01_change_77_prev = x;
    return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
}

void gen_01_change_77_init() {
    this->gen_01_change_77_prev = 0;
}

void gen_01_change_77_reset() {
    this->gen_01_change_77_prev = 0;
}

number gen_01_mtof_78_next(number midivalue, number tuning) {
    RNBO_UNUSED(tuning);

    if (midivalue == this->gen_01_mtof_78_lastInValue && 440 == this->gen_01_mtof_78_lastTuning)
        return this->gen_01_mtof_78_lastOutValue;

    this->gen_01_mtof_78_lastInValue = midivalue;
    this->gen_01_mtof_78_lastTuning = 440;
    number result = 0;

    {
        result = rnbo_exp(.057762265 * (midivalue - 69.0));
    }

    this->gen_01_mtof_78_lastOutValue = 440 * result;
    return this->gen_01_mtof_78_lastOutValue;
}

void gen_01_mtof_78_reset() {
    this->gen_01_mtof_78_lastInValue = 0;
    this->gen_01_mtof_78_lastOutValue = 0;
    this->gen_01_mtof_78_lastTuning = 0;
}

number gen_01_mtof_79_next(number midivalue, number tuning) {
    RNBO_UNUSED(tuning);

    if (midivalue == this->gen_01_mtof_79_lastInValue && 440 == this->gen_01_mtof_79_lastTuning)
        return this->gen_01_mtof_79_lastOutValue;

    this->gen_01_mtof_79_lastInValue = midivalue;
    this->gen_01_mtof_79_lastTuning = 440;
    number result = 0;

    {
        result = rnbo_exp(.057762265 * (midivalue - 69.0));
    }

    this->gen_01_mtof_79_lastOutValue = 440 * result;
    return this->gen_01_mtof_79_lastOutValue;
}

void gen_01_mtof_79_reset() {
    this->gen_01_mtof_79_lastInValue = 0;
    this->gen_01_mtof_79_lastOutValue = 0;
    this->gen_01_mtof_79_lastTuning = 0;
}

void delaytilde_02_del_step() {
    this->delaytilde_02_del_reader++;

    if (this->delaytilde_02_del_reader >= (Int)(this->delaytilde_02_del_buffer->getSize()))
        this->delaytilde_02_del_reader = 0;
}

number delaytilde_02_del_read(number size, Int interp) {
    if (interp == 0) {
        number r = (Int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Int index2 = (Int)(index1 + 1);

        return this->linearinterp(frac, this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
        ));
    } else if (interp == 1) {
        number r = (Int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? 1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->cubicinterp(frac, this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_02_del_wrap))
        ));
    } else if (interp == 6) {
        number r = (Int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? 1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->fastcubicinterp(frac, this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_02_del_wrap))
        ));
    } else if (interp == 2) {
        number r = (Int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? 1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->splineinterp(frac, this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_02_del_wrap))
        ));
    } else if (interp == 7) {
        number r = (Int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? 1 + this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);
        Index index5 = (Index)(index4 + 1);
        Index index6 = (Index)(index5 + 1);

        return this->spline6interp(frac, this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index5 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index6 & (BinOpInt)this->delaytilde_02_del_wrap))
        ));
    } else if (interp == 3) {
        number r = (Int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);

        return this->cosineinterp(frac, this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
        ), this->delaytilde_02_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_02_del_wrap))
        ));
    }

    number r = (Int)(this->delaytilde_02_del_buffer->getSize()) + this->delaytilde_02_del_reader - ((size > this->delaytilde_02_del__maxdelay ? this->delaytilde_02_del__maxdelay : (size < (this->delaytilde_02_del_reader != this->delaytilde_02_del_writer) ? this->delaytilde_02_del_reader != this->delaytilde_02_del_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->delaytilde_02_del_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_02_del_wrap))
    );
}

void delaytilde_02_del_write(number v) {
    this->delaytilde_02_del_writer = this->delaytilde_02_del_reader;
    this->delaytilde_02_del_buffer[(Index)this->delaytilde_02_del_writer] = v;
}

number delaytilde_02_del_next(number v, Int size) {
    number effectiveSize = (size == -1 ? this->delaytilde_02_del__maxdelay : size);
    number val = this->delaytilde_02_del_read(effectiveSize, 0);
    this->delaytilde_02_del_write(v);
    this->delaytilde_02_del_step();
    return val;
}

array<Index, 2> delaytilde_02_del_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->delaytilde_02_del_evaluateSizeExpr(this->sr, this->vs);
        this->delaytilde_02_del_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void delaytilde_02_del_init() {
    auto result = this->delaytilde_02_del_calcSizeInSamples();
    this->delaytilde_02_del__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->delaytilde_02_del_buffer->requestSize(requestedSizeInSamples, 1);
    this->delaytilde_02_del_wrap = requestedSizeInSamples - 1;
}

void delaytilde_02_del_clear() {
    this->delaytilde_02_del_buffer->setZero();
}

void delaytilde_02_del_reset() {
    auto result = this->delaytilde_02_del_calcSizeInSamples();
    this->delaytilde_02_del__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->delaytilde_02_del_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->delaytilde_02_del_buffer);
    this->delaytilde_02_del_wrap = this->delaytilde_02_del_buffer->getSize() - 1;
    this->delaytilde_02_del_clear();

    if (this->delaytilde_02_del_reader >= this->delaytilde_02_del__maxdelay || this->delaytilde_02_del_writer >= this->delaytilde_02_del__maxdelay) {
        this->delaytilde_02_del_reader = 0;
        this->delaytilde_02_del_writer = 0;
    }
}

void delaytilde_02_del_dspsetup() {
    this->delaytilde_02_del_reset();
}

number delaytilde_02_del_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    return samplerate;
}

number delaytilde_02_del_size() {
    return this->delaytilde_02_del__maxdelay;
}

void delaytilde_02_dspsetup(bool force) {
    if ((bool)(this->delaytilde_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->delaytilde_02_rampInSamples = (Int)(this->mstosamps(50));
    this->delaytilde_02_lastDelay = -1;
    this->delaytilde_02_setupDone = true;
    this->delaytilde_02_del_dspsetup();
}

void adsr_01_dspsetup(bool force) {
    if ((bool)(this->adsr_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->adsr_01_mspersamp = (number)1000 / this->sr;
    this->adsr_01_setupDone = true;
}

void change_01_init() {
    this->change_01_prev = this->change_01_input;
}

void message_01_init() {
    this->message_01_set_set(listbase<number, 4>{0, 50, 1, 0});
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

void param_16_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_16_value;
}

void param_16_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_16_value_set(preset["value"]);
}

void param_17_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_17_value;
}

void param_17_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_17_value_set(preset["value"]);
}

void globaltransport_advance() {}

void globaltransport_dspsetup(bool ) {}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

Index getPatcherSerial() const {
    return 0;
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
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

void updateTime(MillisecondTime time, EXTERNALENGINE* engine, bool inProcess = false) {
    RNBO_UNUSED(inProcess);
    RNBO_UNUSED(engine);
    this->_currentTime = time;
    auto offset = rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr));

    if (offset >= (SampleIndex)(this->vs))
        offset = (SampleIndex)(this->vs) - 1;

    if (offset < 0)
        offset = 0;

    this->sampleOffsetIntoNextAudioBuffer = (Index)(offset);
}

void assign_defaults()
{
    delaytilde_01_delay = 0;
    numberobj_01_value = 0;
    numberobj_01_value_setter(numberobj_01_value);
    dspexpr_01_in1 = 0;
    dspexpr_01_in2 = 1;
    dspexpr_02_in1 = 0;
    dspexpr_02_in2 = 1;
    notein_01_channel = 0;
    gen_01_in1 = 0;
    gen_01_terms = 0;
    gen_01_filterOnOff = 0;
    gen_01_cutoffOvertone = 0;
    gen_01_attenuation = 0;
    gen_01_ocillator = 0;
    gen_01_PosNeg = 0;
    gen_01_PosNegSync = 0;
    gen_01_cycleCountToAdd = 0;
    gen_01_cycleCountToSubtract = 0;
    gen_01_termsToAddPerCount = 0;
    gen_01_harmonicSeriesMode = 0;
    gen_01_harmonicRatio = 0;
    dspexpr_03_in1 = 0;
    dspexpr_03_in2 = 0;
    delaytilde_02_delay = 0;
    adsr_01_trigger_number = 0;
    adsr_01_attack = 0;
    adsr_01_decay = 0;
    adsr_01_sustain = 0;
    adsr_01_release = 0;
    adsr_01_legato = false;
    adsr_01_maxsustain = -1;
    expr_01_in1 = 0;
    expr_01_in2 = 127;
    expr_01_out1 = 0;
    linetilde_01_time = 10;
    linetilde_01_keepramp = true;
    change_01_input = 0;
    change_01_out = 0;
    linetilde_02_time = 0;
    linetilde_02_keepramp = false;
    loadmess_01_message = { 50 };
    mstosamps_01_ms = 0;
    param_01_value = 0;
    param_02_value = 100;
    param_03_value = 10;
    param_04_value = 1;
    expr_06_in1 = 0;
    expr_06_in2 = 1;
    expr_06_out1 = 0;
    expr_07_in1 = 0;
    expr_07_in2 = 100;
    expr_07_out1 = 0;
    expr_08_in1 = 0;
    expr_08_in2 = 2;
    expr_08_out1 = 0;
    param_05_value = 0.5;
    param_06_value = 1;
    param_07_value = 2;
    param_08_value = 0;
    param_09_value = 1;
    expr_14_in1 = 0;
    expr_14_in2 = 100;
    expr_14_out1 = 0;
    param_10_value = 1000;
    param_11_value = 80;
    param_12_value = 1;
    param_13_value = 0;
    param_14_value = 1;
    param_15_value = 1;
    param_16_value = 1;
    param_17_value = 1;
    ctlin_01_input = 0;
    ctlin_01_controller = 0;
    ctlin_01_channel = -1;
    expr_02_in1 = 0;
    expr_02_in2 = 0.007874015748;
    expr_02_out1 = 0;
    ctlin_02_input = 0;
    ctlin_02_controller = 0;
    ctlin_02_channel = -1;
    expr_03_in1 = 0;
    expr_03_in2 = 0.007874015748;
    expr_03_out1 = 0;
    ctlin_03_input = 0;
    ctlin_03_controller = 0;
    ctlin_03_channel = -1;
    expr_04_in1 = 0;
    expr_04_in2 = 0.007874015748;
    expr_04_out1 = 0;
    ctlin_04_input = 0;
    ctlin_04_controller = 0;
    ctlin_04_channel = -1;
    expr_05_in1 = 0;
    expr_05_in2 = 0.007874015748;
    expr_05_out1 = 0;
    ctlin_05_input = 0;
    ctlin_05_controller = 0;
    ctlin_05_channel = -1;
    expr_09_in1 = 0;
    expr_09_in2 = 0.007874015748;
    expr_09_out1 = 0;
    ctlin_06_input = 0;
    ctlin_06_controller = 0;
    ctlin_06_channel = -1;
    expr_10_in1 = 0;
    expr_10_in2 = 0.007874015748;
    expr_10_out1 = 0;
    ctlin_07_input = 0;
    ctlin_07_controller = 0;
    ctlin_07_channel = -1;
    expr_11_in1 = 0;
    expr_11_in2 = 0.007874015748;
    expr_11_out1 = 0;
    ctlin_08_input = 0;
    ctlin_08_controller = 0;
    ctlin_08_channel = -1;
    expr_12_in1 = 0;
    expr_12_in2 = 0.007874015748;
    expr_12_out1 = 0;
    ctlin_09_input = 0;
    ctlin_09_controller = 0;
    ctlin_09_channel = -1;
    expr_13_in1 = 0;
    expr_13_in2 = 0.007874015748;
    expr_13_out1 = 0;
    ctlin_10_input = 0;
    ctlin_10_controller = 0;
    ctlin_10_channel = -1;
    expr_15_in1 = 0;
    expr_15_in2 = 0.007874015748;
    expr_15_out1 = 0;
    ctlin_11_input = 0;
    ctlin_11_controller = 0;
    ctlin_11_channel = -1;
    expr_16_in1 = 0;
    expr_16_in2 = 0.007874015748;
    expr_16_out1 = 0;
    ctlin_12_input = 0;
    ctlin_12_controller = 0;
    ctlin_12_channel = -1;
    expr_17_in1 = 0;
    expr_17_in2 = 0.007874015748;
    expr_17_out1 = 0;
    ctlin_13_input = 0;
    ctlin_13_controller = 0;
    ctlin_13_channel = -1;
    expr_18_in1 = 0;
    expr_18_in2 = 0.007874015748;
    expr_18_out1 = 0;
    ctlin_14_input = 0;
    ctlin_14_controller = 0;
    ctlin_14_channel = -1;
    expr_19_in1 = 0;
    expr_19_in2 = 0.007874015748;
    expr_19_out1 = 0;
    ctlin_15_input = 0;
    ctlin_15_controller = 0;
    ctlin_15_channel = -1;
    expr_20_in1 = 0;
    expr_20_in2 = 0.007874015748;
    expr_20_out1 = 0;
    ctlin_16_input = 0;
    ctlin_16_controller = 0;
    ctlin_16_channel = -1;
    expr_21_in1 = 0;
    expr_21_in2 = 0.007874015748;
    expr_21_out1 = 0;
    ctlin_17_input = 0;
    ctlin_17_controller = 0;
    ctlin_17_channel = -1;
    expr_22_in1 = 0;
    expr_22_in2 = 0.007874015748;
    expr_22_out1 = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    signals[1] = nullptr;
    signals[2] = nullptr;
    signals[3] = nullptr;
    signals[4] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.000022675736961451248;
    delaytilde_01_lastDelay = -1;
    delaytilde_01_crossfadeDelay = 0;
    delaytilde_01_ramp = 0;
    delaytilde_01_rampInSamples = 0;
    delaytilde_01_del__maxdelay = 0;
    delaytilde_01_del_sizemode = 0;
    delaytilde_01_del_wrap = 0;
    delaytilde_01_del_reader = 0;
    delaytilde_01_del_writer = 0;
    delaytilde_01_setupDone = false;
    numberobj_01_currentFormat = 6;
    numberobj_01_lastValue = 0;
    notein_01_status = 0;
    notein_01_byte1 = -1;
    notein_01_inchan = 0;
    gen_01_sampleCount_value = 0;
    gen_01_change_8_prev = 0;
    gen_01_change_9_prev = 0;
    gen_01_change_10_prev = 0;
    gen_01_mtof_11_lastInValue = 0;
    gen_01_mtof_11_lastOutValue = 0;
    gen_01_mtof_11_lastTuning = 0;
    gen_01_change_70_prev = 0;
    gen_01_change_71_prev = 0;
    gen_01_change_72_prev = 0;
    gen_01_change_73_prev = 0;
    gen_01_change_74_prev = 0;
    gen_01_change_75_prev = 0;
    gen_01_change_76_prev = 0;
    gen_01_change_77_prev = 0;
    gen_01_mtof_78_lastInValue = 0;
    gen_01_mtof_78_lastOutValue = 0;
    gen_01_mtof_78_lastTuning = 0;
    gen_01_mtof_79_lastInValue = 0;
    gen_01_mtof_79_lastOutValue = 0;
    gen_01_mtof_79_lastTuning = 0;
    delaytilde_02_lastDelay = -1;
    delaytilde_02_crossfadeDelay = 0;
    delaytilde_02_ramp = 0;
    delaytilde_02_rampInSamples = 0;
    delaytilde_02_del__maxdelay = 0;
    delaytilde_02_del_sizemode = 0;
    delaytilde_02_del_wrap = 0;
    delaytilde_02_del_reader = 0;
    delaytilde_02_del_writer = 0;
    delaytilde_02_setupDone = false;
    adsr_01_phase = 1;
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
    linetilde_02_currentValue = 0;
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
    param_16_lastValue = 0;
    param_17_lastValue = 0;
    ctlin_01_status = 0;
    ctlin_01_byte1 = -1;
    ctlin_01_inchan = 0;
    ctlin_02_status = 0;
    ctlin_02_byte1 = -1;
    ctlin_02_inchan = 0;
    ctlin_03_status = 0;
    ctlin_03_byte1 = -1;
    ctlin_03_inchan = 0;
    ctlin_04_status = 0;
    ctlin_04_byte1 = -1;
    ctlin_04_inchan = 0;
    ctlin_05_status = 0;
    ctlin_05_byte1 = -1;
    ctlin_05_inchan = 0;
    ctlin_06_status = 0;
    ctlin_06_byte1 = -1;
    ctlin_06_inchan = 0;
    ctlin_07_status = 0;
    ctlin_07_byte1 = -1;
    ctlin_07_inchan = 0;
    ctlin_08_status = 0;
    ctlin_08_byte1 = -1;
    ctlin_08_inchan = 0;
    ctlin_09_status = 0;
    ctlin_09_byte1 = -1;
    ctlin_09_inchan = 0;
    ctlin_10_status = 0;
    ctlin_10_byte1 = -1;
    ctlin_10_inchan = 0;
    ctlin_11_status = 0;
    ctlin_11_byte1 = -1;
    ctlin_11_inchan = 0;
    ctlin_12_status = 0;
    ctlin_12_byte1 = -1;
    ctlin_12_inchan = 0;
    ctlin_13_status = 0;
    ctlin_13_byte1 = -1;
    ctlin_13_inchan = 0;
    ctlin_14_status = 0;
    ctlin_14_byte1 = -1;
    ctlin_14_inchan = 0;
    ctlin_15_status = 0;
    ctlin_15_byte1 = -1;
    ctlin_15_inchan = 0;
    ctlin_16_status = 0;
    ctlin_16_byte1 = -1;
    ctlin_16_inchan = 0;
    ctlin_17_status = 0;
    ctlin_17_byte1 = -1;
    ctlin_17_inchan = 0;
    globaltransport_tempo = nullptr;
    globaltransport_state = nullptr;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

    // data ref strings
    struct DataRefStrings {
    	static constexpr auto& name0 = "delaytilde_01_del_bufferobj";
    	static constexpr auto& file0 = "";
    	static constexpr auto& tag0 = "buffer~";
    	static constexpr auto& name1 = "phaseStore";
    	static constexpr auto& file1 = "";
    	static constexpr auto& tag1 = "buffer~";
    	static constexpr auto& name2 = "manageParam";
    	static constexpr auto& file2 = "";
    	static constexpr auto& tag2 = "buffer~";
    	static constexpr auto& name3 = "RNBODefaultMtofLookupTable256";
    	static constexpr auto& file3 = "";
    	static constexpr auto& tag3 = "buffer~";
    	static constexpr auto& name4 = "delaytilde_02_del_bufferobj";
    	static constexpr auto& file4 = "";
    	static constexpr auto& tag4 = "buffer~";
    	DataRefStrings* operator->() { return this; }
    	const DataRefStrings* operator->() const { return this; }
    };

    DataRefStrings dataRefStrings;

// member variables

    number delaytilde_01_delay;
    number numberobj_01_value;
    number dspexpr_01_in1;
    number dspexpr_01_in2;
    number dspexpr_02_in1;
    number dspexpr_02_in2;
    number notein_01_channel;
    number gen_01_in1;
    number gen_01_terms;
    number gen_01_filterOnOff;
    number gen_01_cutoffOvertone;
    number gen_01_attenuation;
    number gen_01_ocillator;
    number gen_01_PosNeg;
    number gen_01_PosNegSync;
    number gen_01_cycleCountToAdd;
    number gen_01_cycleCountToSubtract;
    number gen_01_termsToAddPerCount;
    number gen_01_harmonicSeriesMode;
    number gen_01_harmonicRatio;
    number dspexpr_03_in1;
    number dspexpr_03_in2;
    number delaytilde_02_delay;
    number adsr_01_trigger_number;
    number adsr_01_attack;
    number adsr_01_decay;
    number adsr_01_sustain;
    number adsr_01_release;
    number adsr_01_legato;
    number adsr_01_maxsustain;
    number expr_01_in1;
    number expr_01_in2;
    number expr_01_out1;
    list linetilde_01_segments;
    number linetilde_01_time;
    number linetilde_01_keepramp;
    number change_01_input;
    number change_01_out;
    list message_01_set;
    list linetilde_02_segments;
    number linetilde_02_time;
    number linetilde_02_keepramp;
    list loadmess_01_message;
    number mstosamps_01_ms;
    number param_01_value;
    number param_02_value;
    number param_03_value;
    number param_04_value;
    number expr_06_in1;
    number expr_06_in2;
    number expr_06_out1;
    number expr_07_in1;
    number expr_07_in2;
    number expr_07_out1;
    number expr_08_in1;
    number expr_08_in2;
    number expr_08_out1;
    number param_05_value;
    number param_06_value;
    number param_07_value;
    number param_08_value;
    number param_09_value;
    number expr_14_in1;
    number expr_14_in2;
    number expr_14_out1;
    number param_10_value;
    number param_11_value;
    number param_12_value;
    number param_13_value;
    number param_14_value;
    number param_15_value;
    number param_16_value;
    number param_17_value;
    number ctlin_01_input;
    number ctlin_01_controller;
    number ctlin_01_channel;
    number expr_02_in1;
    number expr_02_in2;
    number expr_02_out1;
    number ctlin_02_input;
    number ctlin_02_controller;
    number ctlin_02_channel;
    number expr_03_in1;
    number expr_03_in2;
    number expr_03_out1;
    number ctlin_03_input;
    number ctlin_03_controller;
    number ctlin_03_channel;
    number expr_04_in1;
    number expr_04_in2;
    number expr_04_out1;
    number ctlin_04_input;
    number ctlin_04_controller;
    number ctlin_04_channel;
    number expr_05_in1;
    number expr_05_in2;
    number expr_05_out1;
    number ctlin_05_input;
    number ctlin_05_controller;
    number ctlin_05_channel;
    number expr_09_in1;
    number expr_09_in2;
    number expr_09_out1;
    number ctlin_06_input;
    number ctlin_06_controller;
    number ctlin_06_channel;
    number expr_10_in1;
    number expr_10_in2;
    number expr_10_out1;
    number ctlin_07_input;
    number ctlin_07_controller;
    number ctlin_07_channel;
    number expr_11_in1;
    number expr_11_in2;
    number expr_11_out1;
    number ctlin_08_input;
    number ctlin_08_controller;
    number ctlin_08_channel;
    number expr_12_in1;
    number expr_12_in2;
    number expr_12_out1;
    number ctlin_09_input;
    number ctlin_09_controller;
    number ctlin_09_channel;
    number expr_13_in1;
    number expr_13_in2;
    number expr_13_out1;
    number ctlin_10_input;
    number ctlin_10_controller;
    number ctlin_10_channel;
    number expr_15_in1;
    number expr_15_in2;
    number expr_15_out1;
    number ctlin_11_input;
    number ctlin_11_controller;
    number ctlin_11_channel;
    number expr_16_in1;
    number expr_16_in2;
    number expr_16_out1;
    number ctlin_12_input;
    number ctlin_12_controller;
    number ctlin_12_channel;
    number expr_17_in1;
    number expr_17_in2;
    number expr_17_out1;
    number ctlin_13_input;
    number ctlin_13_controller;
    number ctlin_13_channel;
    number expr_18_in1;
    number expr_18_in2;
    number expr_18_out1;
    number ctlin_14_input;
    number ctlin_14_controller;
    number ctlin_14_channel;
    number expr_19_in1;
    number expr_19_in2;
    number expr_19_out1;
    number ctlin_15_input;
    number ctlin_15_controller;
    number ctlin_15_channel;
    number expr_20_in1;
    number expr_20_in2;
    number expr_20_out1;
    number ctlin_16_input;
    number ctlin_16_controller;
    number ctlin_16_channel;
    number expr_21_in1;
    number expr_21_in2;
    number expr_21_out1;
    number ctlin_17_input;
    number ctlin_17_controller;
    number ctlin_17_channel;
    number expr_22_in1;
    number expr_22_in2;
    number expr_22_out1;
    MillisecondTime _currentTime;
    ENGINE _internalEngine;
    UInt64 audioProcessSampleCount;
    Index sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[5];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    number delaytilde_01_lastDelay;
    number delaytilde_01_crossfadeDelay;
    number delaytilde_01_ramp;
    Int delaytilde_01_rampInSamples;
    Float64BufferRef delaytilde_01_del_buffer;
    Index delaytilde_01_del__maxdelay;
    Int delaytilde_01_del_sizemode;
    Index delaytilde_01_del_wrap;
    Int delaytilde_01_del_reader;
    Int delaytilde_01_del_writer;
    bool delaytilde_01_setupDone;
    Int numberobj_01_currentFormat;
    number numberobj_01_lastValue;
    Int notein_01_status;
    Int notein_01_byte1;
    Int notein_01_inchan;
    number gen_01_sampleCount_value;
    SampleBufferRef gen_01_phaseStore;
    SampleBufferRef gen_01_manageParam;
    number gen_01_change_8_prev;
    number gen_01_change_9_prev;
    number gen_01_change_10_prev;
    number gen_01_mtof_11_lastInValue;
    number gen_01_mtof_11_lastOutValue;
    number gen_01_mtof_11_lastTuning;
    SampleBufferRef gen_01_mtof_11_buffer;
    number gen_01_change_70_prev;
    number gen_01_change_71_prev;
    number gen_01_change_72_prev;
    number gen_01_change_73_prev;
    number gen_01_change_74_prev;
    number gen_01_change_75_prev;
    number gen_01_change_76_prev;
    number gen_01_change_77_prev;
    number gen_01_mtof_78_lastInValue;
    number gen_01_mtof_78_lastOutValue;
    number gen_01_mtof_78_lastTuning;
    SampleBufferRef gen_01_mtof_78_buffer;
    number gen_01_mtof_79_lastInValue;
    number gen_01_mtof_79_lastOutValue;
    number gen_01_mtof_79_lastTuning;
    SampleBufferRef gen_01_mtof_79_buffer;
    number delaytilde_02_lastDelay;
    number delaytilde_02_crossfadeDelay;
    number delaytilde_02_ramp;
    Int delaytilde_02_rampInSamples;
    Float64BufferRef delaytilde_02_del_buffer;
    Index delaytilde_02_del__maxdelay;
    Int delaytilde_02_del_sizemode;
    Index delaytilde_02_del_wrap;
    Int delaytilde_02_del_reader;
    Int delaytilde_02_del_writer;
    bool delaytilde_02_setupDone;
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
    number change_01_prev;
    list linetilde_02_activeRamps;
    number linetilde_02_currentValue;
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
    number param_16_lastValue;
    number param_17_lastValue;
    Int ctlin_01_status;
    Int ctlin_01_byte1;
    Int ctlin_01_inchan;
    Int ctlin_02_status;
    Int ctlin_02_byte1;
    Int ctlin_02_inchan;
    Int ctlin_03_status;
    Int ctlin_03_byte1;
    Int ctlin_03_inchan;
    Int ctlin_04_status;
    Int ctlin_04_byte1;
    Int ctlin_04_inchan;
    Int ctlin_05_status;
    Int ctlin_05_byte1;
    Int ctlin_05_inchan;
    Int ctlin_06_status;
    Int ctlin_06_byte1;
    Int ctlin_06_inchan;
    Int ctlin_07_status;
    Int ctlin_07_byte1;
    Int ctlin_07_inchan;
    Int ctlin_08_status;
    Int ctlin_08_byte1;
    Int ctlin_08_inchan;
    Int ctlin_09_status;
    Int ctlin_09_byte1;
    Int ctlin_09_inchan;
    Int ctlin_10_status;
    Int ctlin_10_byte1;
    Int ctlin_10_inchan;
    Int ctlin_11_status;
    Int ctlin_11_byte1;
    Int ctlin_11_inchan;
    Int ctlin_12_status;
    Int ctlin_12_byte1;
    Int ctlin_12_inchan;
    Int ctlin_13_status;
    Int ctlin_13_byte1;
    Int ctlin_13_inchan;
    Int ctlin_14_status;
    Int ctlin_14_byte1;
    Int ctlin_14_inchan;
    Int ctlin_15_status;
    Int ctlin_15_byte1;
    Int ctlin_15_inchan;
    Int ctlin_16_status;
    Int ctlin_16_byte1;
    Int ctlin_16_inchan;
    Int ctlin_17_status;
    Int ctlin_17_byte1;
    Int ctlin_17_inchan;
    signal globaltransport_tempo;
    signal globaltransport_state;
    number stackprotect_count;
    DataRef delaytilde_01_del_bufferobj;
    DataRef phaseStore;
    DataRef manageParam;
    DataRef RNBODefaultMtofLookupTable256;
    DataRef delaytilde_02_del_bufferobj;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    bool _isInitialized = false;
};

static PatcherInterface* creaternbomatic()
{
    return new rnbomatic<EXTERNALENGINE>();
}

#ifndef RNBO_NO_PATCHERFACTORY
extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction()
#else
extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction()
#endif
{
    return creaternbomatic;
}

#ifndef RNBO_NO_PATCHERFACTORY
extern "C" void SetLogger(Logger* logger)
#else
void rnbomaticSetLogger(Logger* logger)
#endif
{
    console = logger;
}

} // end RNBO namespace

