using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SSelectCam : MonoBehaviour
{
    //--- 長谷川 2023/04/18 -----------------------------------
    //=== スクリプト用変数 =================================
    //--- PlayerControllerScript
    private PlayerController playerController;
    //=== スクリプト用変数 =================================
    //--- 長谷川 2023/04/18 -----------------------------------

    public Transform target;
    //public GameObject Planet;
    public bool LookAtTarget;
    Easing easing;

    //スタートと終わりの目印
    public Transform Point1Marker;
    public Transform Point2Marker;
    public bool selected = false, first = true;
    // スピード
    public float time = 1.0F;
    public int EaseNum = 1;
    //二点間の距離を入れる
    private float distance_two;
    private float distance_Angle;
    public float timer = 0.0f;
    private bool isCalledOnce1 = false, isCalledOnce2 = false;
    [SerializeField] private Vector3 _forward = Vector3.forward;
    SelectManager SelectPlanet;
    GameObject SelectObj;
    public bool Moving = false;
    bool bOldMoving = false;

    static public bool FirstPos = true;
    static public bool ModelCameraPos = false;

    void Start()
    {
        //--- 長谷川 2023/04/18 -----------------------------------
        //=== スクリプト用変数 =================================
        //--- インスタンス化
        this.playerController = FindObjectOfType<PlayerController>();
        //=== スクリプト用変数 =================================
        //--- 長谷川 2023/04/18 -----------------------------------

        easing = GameObject.Find("Main Camera").GetComponent<Easing>();
        SelectObj = GameObject.Find("SelectManager");
        SelectPlanet = SelectObj.GetComponent<SelectManager>();

        // フラグ
        FirstPos = true;
        ModelCameraPos = false;
        bOldMoving = Moving = false;

        //二点間の距離を代入(スピード調整に使う)
    }

    void Update()
    {
        if (bOldMoving != Moving)
            timer = 0.0f;

        bOldMoving = Moving;

        timer += Time.deltaTime;
        // 現在の位置
        float present_Location = timer / time;
        //ベクトル
        var dir = target.position - transform.position;

        if (!Moving)
        {
            timer = 0.0f;

            if (selected)
            {
                transform.position = Point2Marker.position;
                transform.eulerAngles = Point2Marker.eulerAngles;
            }

            return;
        }

        if (selected == true)// 近づき
        {
            if (SelectManager.selected == "GameScene1") { Point2Marker = GameObject.Find("GS0").transform; };
            if (SelectManager.selected == "FireStage") { Point2Marker = GameObject.Find("GS1").transform; };
            if (SelectManager.selected == "SlimeStage") { Point2Marker = GameObject.Find("GS2").transform; };
            if (SelectManager.selected == "IceStage") { Point2Marker = GameObject.Find("GS3").transform; };

            first = false;
            if (!isCalledOnce1)
            {
                isCalledOnce2 = false;
                isCalledOnce1 = true;
                timer = 0;

            }


            // オブジェクトの移動
            if (present_Location < 1.0f)
            {
                FirstPos = false;
                //==========================================================================================================================================
                //
                //座標移動　オブジェクトの位置＝直線移動で補完（始点オブジェクト座標、終点オブジェクト座標、Easing.cs中補完関数呼び出し（移動の割合、イージング番号））
                //
                //==========================================================================================================================================
                transform.position = Vector3.Lerp(Point1Marker.position, Point2Marker.position, easing.Set(present_Location, EaseNum));
                //transform.eulerAngles = Vector3.Lerp(Point1Marker.eulerAngles, Point2Marker.eulerAngles, easing.Set(present_Location, EaseNum));
                //transform.right
                //transform.RotateAround(target.transform.position, transform.right,xSpeed);
                if (LookAtTarget == false)
                {//==========================================================================================================================================
                 //
                 //角度変更①（始点終点オブジェクトの角度を使用する場合）　
                 //
                 //オブジェクトの角度＝直線移動で補完（始点オブジェクト角度、終点オブジェクト角度、Easing.cs中補完関数呼び出し（移動の割合、イージング番号））
                 //
                 //==========================================================================================================================================

                    transform.eulerAngles = Vector3.Lerp(Point1Marker.eulerAngles, Point2Marker.eulerAngles, easing.Set(present_Location, EaseNum));
                }
                else
                {  //==========================================================================================================================================
                   //
                   //角度変更②（自身の座標とターゲットに指定したオブジェクト座標の間のベクトルの角度を使用する場合）
                   //
                   //lookAtRotation:指定された forward と upwards 方向に回転  
                   //
                   //offsetRotation:fromDirection から toDirection への回転を作成します。
                   //
                   //Quaternion LookRotation (Vector3 forward, Vector3 upwards= Vector3.up);
                   //
                   //public static Quaternion FromToRotation (Vector3 fromDirection, Vector3 toDirection);
                   //
                   //角度変更②に星の位置とカメラの位置の間のベクトルでカメラの上向きベクトルを調整するコードを書いてほしいです。　dirplanetが使えると思います。
                   //
                   //==========================================================================================================================================

                    var lookAtRotation = Quaternion.LookRotation(dir, Vector3.up);
                    var offsetRotation = Quaternion.FromToRotation(_forward, Vector3.forward);
                    transform.rotation = lookAtRotation * offsetRotation;
                }
            }
            else // 終点
            {
                Moving = false;
                transform.position = Point2Marker.position;
                transform.eulerAngles = Point2Marker.eulerAngles;
                ModelCameraPos = true;
            };
        }
        else if (!first)// 戻る
        {
            ModelCameraPos = false;

            if (!isCalledOnce2)
            {
                isCalledOnce1 = false;
                isCalledOnce2 = true;
                timer = 0;

            }

            // オブジェクトの移動
            if (present_Location < 1.0f)
            {
                transform.position = Vector3.Lerp(Point2Marker.position, Point1Marker.position, easing.Set(present_Location, EaseNum));
                //transform.eulerAngles = Vector3.Lerp(Point1Marker.eulerAngles, Point2Marker.eulerAngles, easing.Set(present_Location, EaseNum));
                //transform.right
                //transform.RotateAround(target.transform.position, transform.right,xSpeed);
                if (LookAtTarget == false)
                {
                    transform.eulerAngles = Vector3.Lerp(Point2Marker.eulerAngles, Point1Marker.eulerAngles, easing.Set(present_Location, EaseNum));
                }
                else
                {
                    var lookAtRotation = Quaternion.LookRotation(dir, Vector3.up);
                    var offsetRotation = Quaternion.FromToRotation(_forward, Vector3.forward);
                    transform.rotation = lookAtRotation * offsetRotation;
                }
            }
            else
            {
                FirstPos = true;
                Moving = false;
                transform.position = Point1Marker.position;
                transform.eulerAngles = Point1Marker.eulerAngles;
            };
        }
    }
}