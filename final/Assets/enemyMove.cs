using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class enemyMove : MonoBehaviour
{
    public float count_time;
    private float counter;
    public Animator anim;
    public GameObject[] waypoints;
    public int currentWaypointIndex = 0;
    public float speed = 1f;
    public float RotationSpeed;
    private Quaternion _lookRotation;
    private Vector3 _direction;
    // Start is called before the first frame update
    void Start()
    {
        counter = count_time;
    }

    // Update is called once per frame
    void Update()
    {
    	if(counter >= 2){
            anim.SetBool("Run Forward", true);
        }
        else if(counter >= 1){
            anim.SetBool("Run Forward", false);
            anim.SetBool("Attack 01", true);
            
        }
        else if(counter >= 0){
            anim.SetBool("Attack 01", false);
            anim.SetBool("Attack 02", true);
        }
        else{
            anim.SetBool("Attack 02", false);
            counter = count_time;
        }
        counter -= Time.deltaTime;
        
        if(Vector3.Distance(transform.position, waypoints[currentWaypointIndex].transform.position) < .1f){
            currentWaypointIndex++;
            if(currentWaypointIndex >= waypoints.Length){
                currentWaypointIndex = 0;
            }
            //_direction = (waypoints[currentWaypointIndex].transform.position - transform.position).normalized;
            
            
        }
        transform.position = Vector3.MoveTowards(transform.position, waypoints[currentWaypointIndex].transform.position, speed * Time.deltaTime);
        _lookRotation = Quaternion.LookRotation((waypoints[currentWaypointIndex].transform.position - transform.position).normalized);
            transform.rotation = Quaternion.Slerp(transform.rotation, _lookRotation, Time.deltaTime * RotationSpeed);
        
    }
}
