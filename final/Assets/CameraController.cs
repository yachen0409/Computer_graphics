using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{
    public Transform target;
    public Vector3 offset;
    public float rotateSpeed;
    public Transform Pivot;
    public bool useoffsetvalue;
    
    public float maxviewangle;
    public float minviewangle;
    
    public bool inverty;
    // Start is called before the first frame update
    void Start()
    {
        if(!useoffsetvalue){
            offset = target.position - transform.position;
        }
        Pivot.transform.position = target.transform.position;
        Pivot.transform.parent = null;
        Cursor.lockState = CursorLockMode.Locked;
    }

    // Update is called once per frame
    void LateUpdate()
    {
        Pivot.transform.position = target.transform.position;
        float horizontal = Input.GetAxis("Mouse X") * rotateSpeed;
        Pivot.Rotate(0, horizontal, 0);
        float vertical = Input.GetAxis("Mouse Y") * rotateSpeed;
        if(inverty){
            Pivot.Rotate(vertical, 0, 0);
        }
        else{
            Pivot.Rotate(-vertical, 0, 0);
        }
        if(Pivot.rotation.eulerAngles.x > maxviewangle && Pivot.rotation.eulerAngles.x < 180f){
            Pivot.rotation = Quaternion.Euler(maxviewangle, 0, 0);
        }
        if(Pivot.rotation.eulerAngles.x > 180 && Pivot.rotation.eulerAngles.x < 360f+minviewangle){
            Pivot.rotation = Quaternion.Euler(360f + minviewangle, 0, 0);
        }
        
        float desiredXAngle = Pivot.eulerAngles.x;
        float desiredYAngle = Pivot.eulerAngles.y;
        Quaternion rotation = Quaternion.Euler(desiredXAngle, desiredYAngle, 0);
        transform.position = target.position - (rotation * offset);
        if(transform.position.y < target.position.y){
            transform.position = new Vector3(transform.position.x, target.position.y - .5f, transform.position.z);
        }
        transform.LookAt(target);
    }
}
