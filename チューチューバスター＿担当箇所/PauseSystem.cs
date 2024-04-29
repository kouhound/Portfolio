using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;
using UnityEngine.InputSystem;
public class PauseSystem : MonoBehaviour
{
    public bool isPause = false;
    public GameObject obj;
    public GameObject MenuBar;
    public GameObject Number3;
    public GameObject Number2;
    public GameObject Number1;
    public GameObject Numbergo;
    private BossHp boss ;/*.GetComponent<BossHP>().IsBoss*/
    private PlayerController playerController;

    private bool resuming = false;
    [SerializeField] public AudioClip CountDown;
    [SerializeField] public AudioSource audioSource;
    public AudioSource audioSourcePropaty
    { get { return audioSource; } }
    // Start is called before the first frame update
    void Start()
    {
        this.playerController = FindObjectOfType<PlayerController>();





        InitSE();
    }

    // Update is called once per frame
    void Update()
    {
        boss = GameObject.Find("Boss").GetComponent<BossHp>();
        if (Input.GetKeyDown(KeyCode.Escape) && resuming == false && playerController.bIsPlayer && !playerController.GamestartStop && boss.IsBoss/* isPause==false*/)
        {
            PauseGame();
            isPause = true;//�|�[�Y���j���[�ɓ���
        };

        if (isPause)//�|�[�Y�ɓ����Ă���
        {
            obj.SetActive(true);//�|�[�Y���j���[�p�I�u�W�F�N�g�Q�̗L����
            playerController.GamestartStop = true;

        }
        else//�|�[�Y�ɓ����Ă��Ȃ�
        {
            obj.SetActive(false);//�|�[�Y���j���[�p�I�u�W�F�N�g�Q�̖�����
        }
    }
    public void PauseGame()//�|�[�Y�J�n
    {
        Time.timeScale = 0;
    }

    public void ResumeGame()//�|�[�Y�I��
    {
        Time.timeScale = 1;


        StartCoroutine(DelayCoroutime());
    }
    public void InitSE()
    {
        audioSource = GetComponent<AudioSource>();//SE������
    }
    private IEnumerator DelayCoroutime()
    {
        audioSource.PlayOneShot(CountDown);
        resuming = true;
        Debug.Log("Restart:3");
        Number3.SetActive(true);
        yield return new WaitForSeconds(1);
        Debug.Log("Restart:2");
        Number2.SetActive(true);
        yield return new WaitForSeconds(1);
        Debug.Log("Restart:1");
        Number1.SetActive(true);
        yield return new WaitForSeconds(1);
        Debug.Log("Go!");
        Numbergo.SetActive(true);
        playerController.GamestartStop = false;
        resuming = false;
    }
    public void EndGame(int Sceneindex)
    {
        SceneManager.LoadScene(Sceneindex);//�V�[���ړ�
    }

    public void StartButton(InputAction.CallbackContext context)
    {
        if (!context.performed) return; // �����ꂽ�u�Ԃ�Performed�ƂȂ�
        {
            if (resuming == false && playerController.bIsPlayer && !playerController.GamestartStop && boss.IsBoss)
            {
                PauseGame();
                isPause = true;
            }
        }

    }

}
