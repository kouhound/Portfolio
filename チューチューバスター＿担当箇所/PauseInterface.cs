using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.Audio;
using UnityEngine.UI;
using UnityEngine.EventSystems;
public class PauseInterface : MonoBehaviour
{
    public PauseSystem pausesystem;
    Fade m_fade;
    public float SCENE_FADEIN_TIME = 2.0f;
    public float SCENE_FADEOUT_TIME = 2.0f;
    [SerializeField] AudioMixer audioMixer;
    [SerializeField] Slider bgmSlider;
    [SerializeField] Slider seSlider;
    private GameObject th;

    [SerializeField] public AudioClip SE;
    [SerializeField] public AudioSource audioSource;
    public AudioSource audioSourcePropaty
    { get { return audioSource; } }
    void Awake()//オブジェクトが有効化されたときに実行
    {

        // フェード
        m_fade = GameObject.Find("FadePanel").GetComponent<Fade>();
        m_fade.FadeIn(SCENE_FADEIN_TIME);
        bgmSlider.onValueChanged.AddListener(AdjustBGM);//BGMのオーディオミキサーの設定
        seSlider.onValueChanged.AddListener(AdjustSE);//SEのオーディオミキサーの設定

        InitSE();
        //audioSource.PlayOneShot(SE);
    }
    public void InitSE()
    {
        audioSource = GetComponent<AudioSource>();
    }
    void Update()
    {
        if (th != EventSystem.current.currentSelectedGameObject)
        {
            th = EventSystem.current.currentSelectedGameObject;
            audioSource.PlayOneShot(SE); 
        }
       
    }
    public void AdjustBGM(float value)//BGM用スライダーの値を元にオーディオミキサ―の音量を変更する
    {
        value /= 10;
        //-80~0に変換
        var volume = Mathf.Clamp(Mathf.Log10(value) * 20f, -80f, 0f);
        //audioMixerに代入
        audioMixer.SetFloat("BGMVol", volume);
        Debug.Log($"BGM:{volume}");
        audioSource.PlayOneShot(SE);
    }
    public void AdjustSE(float value)//SE用スライダーの値を元にオーディオミキサ―の音量を変更する
    {
        //5段階補正
        value /= 10;
        //-80~0に変換
        var volume = Mathf.Clamp(Mathf.Log10(value) * 20f, -80f, 0f);
        //audioMixerに代入
        audioMixer.SetFloat("SEVol", volume);
        Debug.Log($"SE:{volume}");
        audioSource.PlayOneShot(SE);
    }
    public void ResumeGame()//ポーズ解除
    {

        pausesystem.isPause = false;
        pausesystem.ResumeGame();
    }
    public void EndGame(int Sceneindex)//ステージセレクトに戻る
    {
        //  pausesystem.isPause = false;

        m_fade.FadeOut(SCENE_FADEOUT_TIME, m_fade.SceneChange("StageSelectScene"));
        Time.timeScale = 1;
        //SceneManager.LoadScene(Sceneindex);
    }
}
