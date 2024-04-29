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
    void Awake()//�I�u�W�F�N�g���L�������ꂽ�Ƃ��Ɏ��s
    {

        // �t�F�[�h
        m_fade = GameObject.Find("FadePanel").GetComponent<Fade>();
        m_fade.FadeIn(SCENE_FADEIN_TIME);
        bgmSlider.onValueChanged.AddListener(AdjustBGM);//BGM�̃I�[�f�B�I�~�L�T�[�̐ݒ�
        seSlider.onValueChanged.AddListener(AdjustSE);//SE�̃I�[�f�B�I�~�L�T�[�̐ݒ�

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
    public void AdjustBGM(float value)//BGM�p�X���C�_�[�̒l�����ɃI�[�f�B�I�~�L�T�\�̉��ʂ�ύX����
    {
        value /= 10;
        //-80~0�ɕϊ�
        var volume = Mathf.Clamp(Mathf.Log10(value) * 20f, -80f, 0f);
        //audioMixer�ɑ��
        audioMixer.SetFloat("BGMVol", volume);
        Debug.Log($"BGM:{volume}");
        audioSource.PlayOneShot(SE);
    }
    public void AdjustSE(float value)//SE�p�X���C�_�[�̒l�����ɃI�[�f�B�I�~�L�T�\�̉��ʂ�ύX����
    {
        //5�i�K�␳
        value /= 10;
        //-80~0�ɕϊ�
        var volume = Mathf.Clamp(Mathf.Log10(value) * 20f, -80f, 0f);
        //audioMixer�ɑ��
        audioMixer.SetFloat("SEVol", volume);
        Debug.Log($"SE:{volume}");
        audioSource.PlayOneShot(SE);
    }
    public void ResumeGame()//�|�[�Y����
    {

        pausesystem.isPause = false;
        pausesystem.ResumeGame();
    }
    public void EndGame(int Sceneindex)//�X�e�[�W�Z���N�g�ɖ߂�
    {
        //  pausesystem.isPause = false;

        m_fade.FadeOut(SCENE_FADEOUT_TIME, m_fade.SceneChange("StageSelectScene"));
        Time.timeScale = 1;
        //SceneManager.LoadScene(Sceneindex);
    }
}
