using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SSelectCam : MonoBehaviour
{
    //--- ���J�� 2023/04/18 -----------------------------------
    //=== �X�N���v�g�p�ϐ� =================================
    //--- PlayerControllerScript
    private PlayerController playerController;
    //=== �X�N���v�g�p�ϐ� =================================
    //--- ���J�� 2023/04/18 -----------------------------------

    public Transform target;
    //public GameObject Planet;
    public bool LookAtTarget;
    Easing easing;

    //�X�^�[�g�ƏI���̖ڈ�
    public Transform Point1Marker;
    public Transform Point2Marker;
    public bool selected = false, first = true;
    // �X�s�[�h
    public float time = 1.0F;
    public int EaseNum = 1;
    //��_�Ԃ̋���������
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
        //--- ���J�� 2023/04/18 -----------------------------------
        //=== �X�N���v�g�p�ϐ� =================================
        //--- �C���X�^���X��
        this.playerController = FindObjectOfType<PlayerController>();
        //=== �X�N���v�g�p�ϐ� =================================
        //--- ���J�� 2023/04/18 -----------------------------------

        easing = GameObject.Find("Main Camera").GetComponent<Easing>();
        SelectObj = GameObject.Find("SelectManager");
        SelectPlanet = SelectObj.GetComponent<SelectManager>();

        // �t���O
        FirstPos = true;
        ModelCameraPos = false;
        bOldMoving = Moving = false;

        //��_�Ԃ̋�������(�X�s�[�h�����Ɏg��)
    }

    void Update()
    {
        if (bOldMoving != Moving)
            timer = 0.0f;

        bOldMoving = Moving;

        timer += Time.deltaTime;
        // ���݂̈ʒu
        float present_Location = timer / time;
        //�x�N�g��
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

        if (selected == true)// �߂Â�
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


            // �I�u�W�F�N�g�̈ړ�
            if (present_Location < 1.0f)
            {
                FirstPos = false;
                //==========================================================================================================================================
                //
                //���W�ړ��@�I�u�W�F�N�g�̈ʒu�������ړ��ŕ⊮�i�n�_�I�u�W�F�N�g���W�A�I�_�I�u�W�F�N�g���W�AEasing.cs���⊮�֐��Ăяo���i�ړ��̊����A�C�[�W���O�ԍ��j�j
                //
                //==========================================================================================================================================
                transform.position = Vector3.Lerp(Point1Marker.position, Point2Marker.position, easing.Set(present_Location, EaseNum));
                //transform.eulerAngles = Vector3.Lerp(Point1Marker.eulerAngles, Point2Marker.eulerAngles, easing.Set(present_Location, EaseNum));
                //transform.right
                //transform.RotateAround(target.transform.position, transform.right,xSpeed);
                if (LookAtTarget == false)
                {//==========================================================================================================================================
                 //
                 //�p�x�ύX�@�i�n�_�I�_�I�u�W�F�N�g�̊p�x���g�p����ꍇ�j�@
                 //
                 //�I�u�W�F�N�g�̊p�x�������ړ��ŕ⊮�i�n�_�I�u�W�F�N�g�p�x�A�I�_�I�u�W�F�N�g�p�x�AEasing.cs���⊮�֐��Ăяo���i�ړ��̊����A�C�[�W���O�ԍ��j�j
                 //
                 //==========================================================================================================================================

                    transform.eulerAngles = Vector3.Lerp(Point1Marker.eulerAngles, Point2Marker.eulerAngles, easing.Set(present_Location, EaseNum));
                }
                else
                {  //==========================================================================================================================================
                   //
                   //�p�x�ύX�A�i���g�̍��W�ƃ^�[�Q�b�g�Ɏw�肵���I�u�W�F�N�g���W�̊Ԃ̃x�N�g���̊p�x���g�p����ꍇ�j
                   //
                   //lookAtRotation:�w�肳�ꂽ forward �� upwards �����ɉ�]  
                   //
                   //offsetRotation:fromDirection ���� toDirection �ւ̉�]���쐬���܂��B
                   //
                   //Quaternion LookRotation (Vector3 forward, Vector3 upwards= Vector3.up);
                   //
                   //public static Quaternion FromToRotation (Vector3 fromDirection, Vector3 toDirection);
                   //
                   //�p�x�ύX�A�ɐ��̈ʒu�ƃJ�����̈ʒu�̊Ԃ̃x�N�g���ŃJ�����̏�����x�N�g���𒲐�����R�[�h�������Ăق����ł��B�@dirplanet���g����Ǝv���܂��B
                   //
                   //==========================================================================================================================================

                    var lookAtRotation = Quaternion.LookRotation(dir, Vector3.up);
                    var offsetRotation = Quaternion.FromToRotation(_forward, Vector3.forward);
                    transform.rotation = lookAtRotation * offsetRotation;
                }
            }
            else // �I�_
            {
                Moving = false;
                transform.position = Point2Marker.position;
                transform.eulerAngles = Point2Marker.eulerAngles;
                ModelCameraPos = true;
            };
        }
        else if (!first)// �߂�
        {
            ModelCameraPos = false;

            if (!isCalledOnce2)
            {
                isCalledOnce1 = false;
                isCalledOnce2 = true;
                timer = 0;

            }

            // �I�u�W�F�N�g�̈ړ�
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