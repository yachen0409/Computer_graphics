using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    public int a = 0;
    public int b = 0;
    public int c = 0;
    public Vector3 startPos;
    public GameObject movingplain;
    public Vector3 movingdir;
    public bool onPlain = false;
    public float movespeed;
    //public Rigidbody theRB;
    public float jumpvalue;
    public CharacterController controller;
    public AudioSource jumpvoice;
    public AudioSource jumpvoice2;
    
    private Vector3 moveDirection;
    public float gravityScale;
    public Animator anim;
    public Transform pivot;
    public float rotatespeed;
    public GameObject player;
    public Vector3 playerPosition;
    public float knockBackForce;
    public float knockBackTime;
    private float knockBackCounter;
    public static Vector3 respawnPoint;
    // Start is called before the first frame update
    void Start()
    {
        //theRB = GetComponent<Rigidbody>();
        c++;
        controller = GetComponent<CharacterController>();
        respawnPoint = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        //theRB.velocity = new Vector3(Input.GetAxis("Horizontal") * movespeed, theRB.velocity.y, Input.GetAxis("Vertical") * movespeed);
        
        //if(Input.GetButtonDown("Jump")){
          //  theRB.velocity = new Vector3(theRB.velocity.x, jumpvalue, theRB.velocity.z);
        //}
        
        //moveDirection = new Vector3(Input.GetAxis("Horizontal") * movespeed, moveDirection.y,  Input.GetAxis("Vertical") * movespeed);
        
        playerPosition = transform.position;
        if(knockBackCounter <= 0){
	    float yStore = moveDirection.y;
	    moveDirection = (transform.forward * Input.GetAxis("Vertical")) + (transform.right * Input.GetAxis("Horizontal"));
	    moveDirection = moveDirection.normalized * movespeed;
	    moveDirection.y = yStore;
	    if(controller.isGrounded){
	        //moveDirection = new Vector3(Input.GetAxis("Horizontal") * movespeed, 0f,  Input.GetAxis("Vertical") * movespeed);
	        moveDirection.y = 0f;
	        if(Input.GetButtonDown("Jump")){
	        //theRB.velocity = new Vector3(theRB.velocity.x, jumpvalue, theRB.velocity.z);
	            jumpvoice.Play();
	            jumpvoice2.Play();
	            moveDirection.y = jumpvalue;
	        }
	    }
        }
        else{
            knockBackCounter -= Time.deltaTime;
        }
        moveDirection.y = moveDirection.y + (Physics.gravity.y * gravityScale * Time.deltaTime);
        anim.SetBool("Run", moveDirection.x != 0 || moveDirection.z != 0);
        anim.SetBool("Turn Head", Input.GetButtonDown("Jump"));
        if(onPlain){
            //Vector3 newPosition = new Vector3();
	    //newPosition.x = movingplain.transform.position.x;
	    //newPosition.y = movingplain.transform.position.y;
	    //newPosition.z = movingplain.transform.position.z;
	    //transform.position = newPosition;
            //transform.SetParent(movingplain.transform);
            //controller.Move((movingplain.transform.position - startPos));
            //startPos = transform.position;
            movingdir = movingplain.GetComponent<WaypointFollower>().movingmove;
            moveDirection += movingdir;
        
        }

        controller.Move(moveDirection * Time.deltaTime);
        if(moveDirection != new Vector3(0, 0, 0)){
            startPos = transform.position;
        }
        if(Input.GetAxis("Horizontal") != 0 || Input.GetAxis("Vertical") != 0){
            transform.rotation = Quaternion.Euler(0f, pivot.rotation.eulerAngles.y, 0f);
            Quaternion newRotation = Quaternion.LookRotation(new Vector3(moveDirection.x, 0f, moveDirection.z));
            player.transform.rotation = Quaternion.Slerp(player.transform.rotation, newRotation, rotatespeed * Time.deltaTime);
        }
        if(player.transform.position.y < -10f){
            FindObjectOfType<HealthManager>().Respawn();
        }
        
        

    }
    public void KnockBack(Vector3 direction){
        knockBackCounter = knockBackTime;
        direction = new Vector3(1f, 1f, 1f);
        moveDirection = direction * knockBackForce;
        moveDirection.y = knockBackForce;
    }
    private void OnTriggerEnter(Collider other)
    {
        if (other.transform.tag == "Moving")
        {
            a++;
            //startPos = transform.position;
            //movingplain = other;
            onPlain = true;
            movingplain = other.gameObject;
            //transform.parent = other.transform;
            //Debug.Log("We are on a moving platform");
        }
        if (other.transform.tag == "super"){
            b++;
            jumpvalue = jumpvalue * 2.5f;
        }
    }
 
    private void OnTriggerExit(Collider other)
    {
        if (other.transform.tag == "Moving")
        {
            a--;
            onPlain = false;
            //transform.parent = null;
        }
        if (other.transform.tag == "super"){
            b--;
            jumpvalue = jumpvalue / 2.5f;
        }
    }
    
    
}
