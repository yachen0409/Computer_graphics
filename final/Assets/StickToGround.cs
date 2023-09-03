using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StickToGround : MonoBehaviour
{
    public GameObject player;
    public int a = 0;
    public bool onPlain = false;
    public Vector3 startPos;
    public Vector3 playPos;
    public Vector3 groundPos;
    // Start is called before the first frame update
    void Start()
    {
        startPos = player.transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        playPos = player.transform.position;
        groundPos = this.transform.position;
        //player.transform.position = startPos + this.transform.position;
        if(onPlain){
            //player.transform.position = startPos + this.transform.position;
            player.transform.SetParent(this.transform);
            //player.transform.position = new Vector3(this.transform.position.x, player.transform.position.y, player.transform.position.z);
        }
        else{
            player.transform.SetParent(null);
        }
        
    }
    //private void OnCollisionEnter(Collision other){
        //if(other.gameObject.tag == "Player"){
            //a++;
            //onPlain = true;
        //}
    //}
    //private void OnCollisionExit(Collision other){
        //if(other.gameObject.tag == "Player"){
            //a--;
            //onPlain = false;
        //}
    //}
    private void OnTriggerEnter(Collider other){
    	if(other.gameObject.tag == "Player"){
    	    a++;
    	    onPlain = true;
    	    //player.transform.parent = transform;
    	    //Vector3 hitDirection = other.transform.position - transform.position;
    	    //hitDirection = hitDirection.normalized;
    	    //FindObjectOfType<HealthManager>().HurtPlayer(damage, hitDirection);
    	    
    	}
    }
    private void OnTriggerExit(Collider other){
    	if(other.gameObject.tag == "Player"){
    	    a--;
    	    onPlain = false;
    	    //player.transform.parent = null;
    	    //Vector3 hitDirection = other.transform.position - transform.position;
    	    //hitDirection = hitDirection.normalized;
    	    //FindObjectOfType<HealthManager>().HurtPlayer(damage, hitDirection);
    	    
    	}
    }
}
