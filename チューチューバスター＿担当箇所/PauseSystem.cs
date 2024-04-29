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
            isPause = true;//ポーズメニューに入る
        };

        if (isPause)//ポーズに入っている
        {
            obj.SetActive(true);//ポーズメニュー用オブジェクト群の有効化
            playerController.GamestartStop = true;

        }
        else//ポーズに入っていない
        {
            obj.SetActive(false);//ポーズメニュー用オブジェクト群の無効化
        }
    }
    public void PauseGame()//ポーズ開始
    {
        Time.timeScale = 0;
    }

    public void ResumeGame()//ポーズ終了
    {
        Time.timeScale = 1;


        StartCoroutine(DelayCoroutime());
    }
    public void InitSE()
    {
        audioSource = GetComponent<AudioSource>();//SE初期化
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
        SceneManager.LoadScene(Sceneindex);//シーン移動
    }

    public void StartButton(InputAction.CallbackContext context)
    {
        if (!context.performed) return; // 押された瞬間でPerformedとなる
        {
            if (resuming == false && playerController.bIsPlayer && !playerController.GamestartStop && boss.IsBoss)
            {
                PauseGame();
                isPause = true;
            }
        }

    }

}
