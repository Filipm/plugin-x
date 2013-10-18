package org.cocos2dx.plugin;

import org.ispeech.SpeechSynthesis;
import org.ispeech.SpeechSynthesisEvent;
import org.ispeech.error.BusyException;
import org.ispeech.error.InvalidApiKeyException;
import org.ispeech.error.NoNetworkException;

import android.app.Activity;
import android.content.Context;
import android.media.AudioManager;
import android.util.Log;

/**
 * Created by Dawid Drozd on 7/12/13.
 */
public class ISpeech extends SpeechSynthesisEvent {

	/**
	 * From Plugin X
	 */
	private boolean m_isDebug = false;
	private Context m_context;
	public final int PluginType = 5;// Raw plugin

	public void setDebugMode(boolean isDebugMode) {
		m_isDebug = isDebugMode;
	}

	/**
	 * From Plugin X
	 */

	static final int INVALID_API_KEY = 1;
	static final int BUSY = 2;
	static final int NO_NETWORK = 3;

	private String m_voiceType;

	public ISpeech(Context context) {
		m_context = context;
	}

	public void setVoiceType(String voiceType) {
		m_voiceType = voiceType;
	}

	public int speak(String text) {
		try {
			SpeechSynthesis speechSynthesis = SpeechSynthesis
					.getInstance((Activity) m_context);
			speechSynthesis.setConnectionTimeout(5000);
			speechSynthesis.setSpeakWhenSilent(true);
			speechSynthesis.setStreamType(AudioManager.STREAM_MUSIC);
			speechSynthesis.setVoiceType(m_voiceType);
			speechSynthesis.speak(text);
			// TODO async
			// speechSynthesis.setSpeechSynthesisEvent(this);

		} catch (InvalidApiKeyException e) {
			e.printStackTrace();
			return INVALID_API_KEY;
		} catch (BusyException e) {
			e.printStackTrace();
			return BUSY;
		} catch (NoNetworkException e) {
			e.printStackTrace();
			return NO_NETWORK;
		}
		return 0; // all ok
	}

	public void onPlaySuccessful() {
		Log.i("", "onPlaySuccessful");
	}

	public void onPlayStopped() {
		Log.i("", "onPlayStopped");
	}

	public void onPlayFailed(Exception e) {
		Log.e("", "onPlayFailed");
		e.printStackTrace();
	}

	public void onPlayStart() {
		Log.i("", "onPlayStart");
	}

	@Override
	public void onPlayCanceled() {
		Log.i("", "onPlayCanceled");
	}
}
